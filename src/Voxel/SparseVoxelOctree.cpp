#include "EarthAuth/Voxel/SparseVoxelOctree.h"
#include "EarthAuth/Terrain/TerrainManager.h"


namespace LabRat
{

    SparseVoxelOctree::SparseVoxelOctree() :m_GridDimension(0), m_SVORootNode(nullptr)
    {

    }

    SparseVoxelOctree::~SparseVoxelOctree()
    {
        ClearSVO(m_SVORootNode);
    }

    auto SparseVoxelOctree::CreateSVOFromInputGrid(double** InputGrid) -> bool
    {
        ClearSVO(m_SVORootNode);
        m_GridDimension = 0;

        //The construction of this is aided by the immensely helpful resource here
        //https://eisenwave.github.io/voxel-compression-docs/svo/svo.html


        //While having just signed "world" coordinates would make life easier, we've decided to go with unsigned
        //This lets us have 0,0,0 be the dead centre - which is hopefully more intuitive to an end user prospective


        //To outline this process;

        //CONSTRUCT OUR SVO - (+ as we are not organised in a morton order code dynamic resizing not as efficient)
        //Num branches <- 8th root of the amount of total voxels32

        //A: FOR EACH COORDINATE IN THE GRID
        //A1: Figure out if there is a voxel here or no from the input grid - if its empty, skip...
        //B: If we need to expand the SVO, do so
        //D: Normalise our position so it fits the data structure
        //E: Convert this normalised position into our octree index
        //F: Use this index to traverse our octree and insert the voxel at the correct location

        //////
        //A
        //////


        m_SVORootNode = new FSVO_Node();

        //TODO ew 3 nested ifs - I wonder if I can make this better (or atleast more readable)

        //TODO could get sizeof InputGrid instead of relying on this static func? Would that be more efficient?
        for (int z_ind = 0; z_ind < TerrainManager::GetGridSize(); ++z_ind)
            for (int y_ind = 0; y_ind < TerrainManager::GetGridSize(); ++y_ind)
                for (int x_ind = 0; x_ind < TerrainManager::GetGridSize(); ++x_ind)
                {


                    //Before we actually fill out a node, we want to establish if this is a node thats empty or full

                    ////
                    //B
                    /////

                    //Calculate the world coordinates that this corresponds to - remember, we want unsigned coords for the world
                    //As an origin in the centre is more intuitive
                    //NTS: IF COORDS ARE OUT OF WACK CONSIDER FLOATING POINT ERROR STUFF HERE
                    const int XCoord = x_ind - std::trunc(float(TerrainManager::GetGridSize()) / 2.f);
                    const int YCoord = y_ind - std::trunc(float(TerrainManager::GetGridSize()) / 2.f);
                    const int ZCoord = z_ind - std::trunc(float(TerrainManager::GetGridSize()) / 2.f);

                    //If the calculated world coords isn't within the bounds of our octree atm, we want to expand!
                    if (!IsPointInBounds(XCoord, YCoord, ZCoord))
                    {
                        if (!GrowSVO(m_SVORootNode))
                            return false;

                        //ATTEMPT A: WHAT IF WE INCREMENT EACH TIME

                        ++m_GridDimension;
                        //TODO HERE - My assumption is, rather than just "incrementing" D, if we are out of bounds, we want to
                        //expand it to
                        const std::string DimMsg = "growing - grid dim: " + std::to_string(m_GridDimension) + "\n";
                        Utils::Debug::PrintDebugText(DimMsg, Utils::EDebugMessageType::EDMT_Info);
                    }

                    //We still wanted to grow the octree if this was empty space (that coord still needs to be able to be repped should something fill it after all...
                    //But at this point, if its empty, no point in going any further.

                    //Perlin noise in range 0-1 - for the sake of this, we will simply compute that as a ratio of how far to the top of the grid we should fill
                    const double Val = InputGrid[y_ind][x_ind];

                    const int ZFillHeight = std::trunc(Val * TerrainManager::GetGridSize());

                    if (ZFillHeight > z_ind)
                    {
                        //We want to calculate the normalised position within the octree, then convert it to an index - so,

                        /////
                        //E
                        /////

                        //Simply subtract the mimimum coordinate possible - which is -2^d

                        const int XNorm = XCoord - std::pow(-2.f, m_GridDimension);
                        const int YNorm = YCoord - std::pow(-2.f, m_GridDimension);
                        const int ZNorm = ZCoord - std::pow(-2.f, m_GridDimension);


                        //////
                        //F
                        //////

                        //Using the output of this, we can figure out where in the SVO this node needs to go
                        const int Ind = Interleave3(XNorm, YNorm, ZNorm);

                        //Using interleaved numbers
                        //                 Once the octree node index is computed, traversing the octree becomes simple:
                        //
                        // For a given index n, we start at the most significant octal digit o and the root node.
                        // We follow the branch number o or construct it if it does not exist yet.
                        // Insert the voxel's color once a leaf node is found.
                        // Repeat until the least significant octal digit is processed.
                        //
                        //psuedo of this:
                        //wed input one of these interleaved nums as an index...
                        // void insert(size_t index, rgb32_t color)
                        // {
                        //     auto &branch = root[(index >> 3) & 0b111]; // use upper digit to get branch
                        //     // ... repeat this process for however many levels of branches there are
                        //     auto &leaf = branch[(index >> 0) & 0b111]; // use lower digit to get leaf
                        //     leaf.color = color;
                        // }
                        // Recursively doing this untill we hit a node that should be
                        //
                        //

                        Insert(Ind, Val);
                    }

                }




        return true;
    }



    auto SparseVoxelOctree::GrowSVO(FSVO_Node* RootNode) -> bool
    {
        //For all the possible children of this node
        for (size_t i = 0; i < 8; ++i)
            //If the node has a child here
            if (RootNode->m_Children[i]) //If there is a child present:
            {
                //Make a new root
                auto NewRoot = new FSVO_Node();
                NewRoot->m_Children[~i & 0b111] = RootNode->m_Children[i];
                RootNode->m_Children[i] = NewRoot;
            }

        //great success
        return true;
    }

    auto SparseVoxelOctree::IsPointInBounds(const int x, const int y, const int z) -> bool
    {
        return (SVOAbs(x) | SVOAbs(y) | SVOAbs(z)) < m_GridDimension;
    }

    auto SparseVoxelOctree::SVOAbs(const int n) -> int
    {
        return n < 0 ? (-n -1) : n;
    }


    auto SparseVoxelOctree::Interleave3(int x, int y, int z) -> int
    {
        return (Interleave_two0(x) << 2) | (Interleave_two0(y) << 1) | Interleave_two0(z);
    }

    auto SparseVoxelOctree::Interleave_two0(int in) -> int
    {
        //https://eisenwave.github.io/voxel-compression-docs/svo/construction.html

        //TODO reliance on magic numbers here is a bit iffy
        constexpr size_t numInputs = 3;
        constexpr uint64_t masks[] = {
            0x9249'2492'4924'9249,
            0x30C3'0C30'C30C'30C3,
            0xF00F'00F0'0F00'F00F,
            0x00FF'0000'FF00'00FF,
            0xFFFF'0000'0000'FFFF
          };

        uint64_t n = in;
        for (int i = 4; i != 1; --i) {
            const auto shift = (numInputs - 1) * (1 << i);
            n |= n << shift;
            n &= masks[i];
        }

        return n;

    }
    auto SparseVoxelOctree::ClearSVO(FSVO_Node* Node) -> void
    {

        if (!Node)
            return;

        //Delete all SVO children, recursively
        for (auto i : Node->m_Children)
            ClearSVO(i);

        //After having deleted all children
        delete m_SVORootNode;

    }

    auto SparseVoxelOctree::Insert(size_t ind, float val) -> void
    {
        auto &branch = m_SVORootNode->m_Children[(ind >> 3) & 0b111]; // use upper digit to get branch

        auto &leaf = branch->m_Children[(ind >> 0) & 0b111];
        leaf->m_VValue = val;
    }

}