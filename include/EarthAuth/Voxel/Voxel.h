
#ifndef BSDCOUNTER_TXT_VOXEL_H
#define BSDCOUNTER_TXT_VOXEL_H

#pragma once

/*GLM includes for matrixes and vectors*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace LabRat
{
    /*The data structure for each "block" in the world - responsible for tracking position, and vertexs for rendering*/
    class Voxel
    {
    public:

        /*Default constructor*/
        Voxel();

    private:

        /*Size of blocks (Length of one edge)*/
        static __int8 BlockSize;


    public:

        /**
         * GETTERS AND SETTERS
         */

        static inline auto GetBlockSize() const -> __int8 { return BlockSize;}

    private:

        /*TEMP BOILERPLATE CODE HERE TO GET THE CUBE OFF THE GROUND - we have packed all the information about locations into one int each*/
        static const int* m_Verts =
        {
            ( 0.0f |  0.0f << 10 |  0.0f << 20),
            (-0.5f |  0.0f << 10 |  0.0f << 20),
            (-0.5f | -0.5f << 10 |  0.0f << 20),
            (0.0f  | -0.5f << 10 |  0.0f << 20),
            ( 0.0f |  0.0f << 10 | -0.5f << 20),
            (-0.5f |  0.0f << 10 | -0.5f << 20),
            (-0.5f | -0.5f << 10 | -0.5f << 20),
            (0.0f  | -0.5f << 10 | -0.5f << 20),

       };

    public:

        static inline auto GetVerts() const -> const float* { return Verts;}


    };
}
#endif //BSDCOUNTER_TXT_VOXEL_H
