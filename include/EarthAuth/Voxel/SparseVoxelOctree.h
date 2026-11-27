
#ifndef BSDCOUNTER_TXT_SPARSEVOXELOCTREE_H
#define BSDCOUNTER_TXT_SPARSEVOXELOCTREE_H

#pragma once


namespace LabRat
{
    /*The nodes that our sparse voxel octree are constructed of - they denote, either a */
    struct FSVO_Node
    {
    public:

        FSVO_Node()
        {
            /*Initialise our children list as all null*/
            for (int i = 0; i < 8; ++i)
                m_Children[i] = nullptr;

            m_Parent = nullptr;
        }

        /*Pointer to our parent node - needed for rearranging if the SVO grows
        */
        FSVO_Node* m_Parent;

        /*
        *Array of children to this node in the Sparse Voxel Octree
        * nullptr / NULL depicts that this "branch" (and all subsequent) are empty
        */
        FSVO_Node* m_Children[8];

        /*Value this represents if this is a  voxel - i.e.: hardness
         * TODO Need to make a seperate "leaf" node DS so we can save on memory...
         */
        float m_VValue;

    };


    /*THE SPARSE VOXEL OCTREE - is our data structure that we will use to represent terrain for the feasibility demonstration.
     * It is a hierachical DS - a tree with branching factor of 8. Null nodes represent an abscence of that point and all child points
     *
     *
     *Further work on this will convert this to a slightly more efficient data structure - a directed acyclic graph
     *The really, really cool thing about those is a lot of implementations I have found in academic papers
     *take an SVO as a starting point - so this starting point shall remain consistent.
     */
    class  SparseVoxelOctree
    {
    public:

        /*Default constructor and destructors*/
        SparseVoxelOctree();
        ~SparseVoxelOctree();

        /*Create an SVO from an input grid*/
        auto CreateSVOFromInputGrid(double** InputGrid) -> bool;

    protected:


        /*Current dimension of the "grid" this SVO describes*/
        int m_GridDimension;

        /*Calculate if a given point coord lies currently within the bounds of our SVO*/
        auto IsPointInBounds(const int x, const int y, const int z) -> bool;

        /*Helper function, a more efficient method of bounds check than "max(abs(x),abs(y),abs(z))>d"*/
        auto SVOAbs(const int n) -> int;

        /*Reset the octree - ensuring the dimension is at 0, and safely deleting all the nodes*/
        auto ClearSVO(FSVO_Node* Node) -> void;

        /*We are trying to add a voxel / node that is out of bounds - grow the tree.*/
        auto GrowSVO(FSVO_Node* RootNode) -> bool;

        /*The root node of our SVO - where everything peels off from*/
        FSVO_Node* m_SVORootNode;


        auto Interleave3(int x, int y, int z) -> int;

        auto Interleave_two0(int in) -> int;

        /*Insert a voxel value at the given index...*/
        auto Insert(size_t ind, float val) -> void;



    };
}


#endif //BSDCOUNTER_TXT_SPARSEVOXELOCTREE_H
