#include "EarthAuth/Voxel/SparseVoxelOctree.h"
#include "EarthAuth/Terrain/TerrainManager.h"


namespace LabRat
{

    SparseVoxelOctree::SparseVoxelOctree() :m_GridDimension(0)
    {

    }

    SparseVoxelOctree::~SparseVoxelOctree()
    {

    }

    auto SparseVoxelOctree::CreateSVOFromInputGrid(double** InputGrid) -> bool
    {
        ClearSVO();

        //The construction of this is aided by the immensely helpful resource here
        //https://eisenwave.github.io/voxel-compression-docs/svo/svo.html

        //While having just signed "world" coordinates would make life easier, we've decided to go with unsigned
        //This lets us have 0,0,0 be the dead centre - which is hopefully more intuitive to an end user prospective


        //To outline this process;

        //A: FOR EACH COORDINATE IN THE GRID

        //B: Figure out if the position of the square we are adding is within the dimensions of the grid
        //C: If so, continue, else expand then continue
        //D: Figure out if, from the input grid, we want to have a voxel here or no.
        //E: Normalise our position so it fits the data structure
        //F: Convert this normalised position into our octree index
        //G: Use this index to traverse our octree and insert the voxel at the correct location

        //////
        //A
        //////


        //TODO ew 3 nested ifs - I wonder if I can make this better (or atleast more readable)

        //TODO could get sizeof InputGrid instead of relying on this static func? Would that be more efficient?
        for (int z_ind = 0; z_ind < TerrainManager::GetGridSize(); ++z_ind)

            for (int y_ind = 0; y_ind < TerrainManager::GetGridSize(); ++y_ind)
                for (int x_ind = 0; x_ind < TerrainManager::GetGridSize(); ++x_ind)
                {
                    ////
                    //B
                    /////

                    //Calculate the world coordinates that this corresponds to - remember, we want unsigned coords for the world
                    //As an origin in the centre is more intuitive
                    //NTS: IF COORDS ARE OUT OF WACK CONSIDER FLOATING POINT ERROR STUFF HERE
                    const int XCoord = x_ind - std::trunc(float(TerrainManager::GetGridSize()) / 2.f);
                    const int YCoord = y_ind - std::trunc(float(TerrainManager::GetGridSize()) / 2.f);
                    const int ZCoord = z_ind - std::trunc(float(TerrainManager::GetGridSize()) / 2.f);


                    if (!IsPointInBounds(XCoord, YCoord, ZCoord))
                    {
                        if (!GrowSVO())
                        {

                        }
                    }

                }




        return true;
    }

    auto SparseVoxelOctree::GrowSVO() -> bool
    {

        for (size_t i = 0; i < 8; ++i)
            if ()


        //great success
        return true;
    }

    auto SparseVoxelOctree::IsPointInBounds(const int x, const int y, const int z) -> bool
    {
        return (SVOAbs(x) | SVOAbs(y) | SVOAbs(z)) >= m_GridDimension;
    }

    auto SparseVoxelOctree::SVOAbs(const int n) -> int
    {
        return n < 0 ? (-n -1) : n;
    }

    auto SparseVoxelOctree::ClearSVO() -> void
    {
        m_GridDimension = 0;

    }
}