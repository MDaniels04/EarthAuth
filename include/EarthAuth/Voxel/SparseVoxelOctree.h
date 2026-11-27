
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

            m_Parent = std::make_shared<FSVO_Node>();
        }

    protected:

        /*Pointer to our parent node - needed for rearranging if the SVO grows
         * weak ptr as non owning reference. Derrived from the shared ptr of the children above.
         */
        std::weak_ptr<FSVO_Node> m_Parent;

    private:

        /*
         *Array of children to this node in the Sparse Voxel Octree
         * nullptr / NULL depicts that this "branch" (and all subsequent) are empty
         */
        std::shared_ptr<FSVO_Node> m_Children[8];

    };

    /*A node that goes at the second to last level - denotes the hardness (or potentially other stuff that we could implement later) of voxels in
     * this 8 "cube"
     *
     */
    struct FSVO_ArrayNode : public FSVO_Node
    {
        FSVO_ArrayNode() : FSVO_Node()
        {
            for (int i = 0; i < 8; ++i)
                m_Children[i] = -1.f;
        }

    private:

        /*TODO more memory efficient implementation than using floats?*/

        /*List storing - for now - the hardness of the voxel present at each point in  the subtree.
         * -1 depicts there is no voxel in that spot. TODO better / unsigned method? we reeeaaallly need to save memory everywhere we can.
         * TODO DAGs (particuarly the method described that discusses symmetry and transform aware) will help this...
         */
        float m_Children[8];
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

    protected:

        FSVO_Node

        /*Create an SVO from an input grid*/
        auto CreateSVOFromInputGrid(double** InputGrid) -> bool;

        /*Current dimension of the "grid" this SVO describes*/
        int m_GridDimension;

        /*Calculate if a given point coord lies currently within the bounds of our SVO*/
        auto IsPointInBounds(const int x, const int y, const int z) -> bool;

        /*Helper function, a more efficient method of bounds check than "max(abs(x),abs(y),abs(z))>d"*/
        auto SVOAbs(const int n) -> int;

        /*Reset the octree - ensuring the dimension is at 0, and safely deleting all the nodes*/
        auto ClearSVO() -> void;

        /*We are trying to add a voxel / node that is out of bounds - grow the tree.*/
        auto GrowSVO() -> bool;

    };
}


#endif //BSDCOUNTER_TXT_SPARSEVOXELOCTREE_H
