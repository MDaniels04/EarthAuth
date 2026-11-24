
#ifndef BSDCOUNTER_TXT_VOXEL_H
#define BSDCOUNTER_TXT_VOXEL_H

#pragma once

/*GLM includes for matrixes and vectors*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    static inline auto GetBlockSize() -> __int8 { return BlockSize;}
};

#endif //BSDCOUNTER_TXT_VOXEL_H
