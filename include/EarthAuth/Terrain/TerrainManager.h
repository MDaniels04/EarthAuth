
#ifndef EARTH_AUTH_TXT_TERRAINMANAGER_H
#define EARTH_AUTH_TXT_TERRAINMANAGER_H

#pragma once

#include <pch.h>



namespace LabRat
{

    class SparseVoxelOctree;

    /**
     *Our terrain manager is responsible for all the functionality we need for the actual terrain the tool needs.
     *
     *It is composed of a  class for handling the terrain representation (for the FD an SVO, for later a DAG(?)),
     *a class for erosion steps
     *
     *And has built in functionality for generating that initial step of terrain,
     */
    class TerrainManager
    {
    public:

        /*Default constructor*/
        TerrainManager();

        /*Default destructor*/
        ~TerrainManager();

        /** Based on parameters passed in, generate terrain from Perlin Noise, and create our SVO...
         *
         * seed -> the seed plugged into the Perlin Noise generator - if blank, we will get one based on time
         */
        auto GenerateTerrainFromParameters(const unsigned int Seed = -1u, const unsigned __int8 NoiseOctaves = 6) -> bool;

    private:

        /*The size of the grid we are using - must be  a cube*/
        static inline unsigned __int16 m_GridSize = 32;

        /*Generate the initial perlin noise for the terrain based on input values, and return the output grid*/
        auto GeneratePerlinNoiseForTerrain(const unsigned int Seed, const unsigned __int8 NoiseOctaves) -> double**;


        /*The data structure that we are representing our terrain in...*/
        std::unique_ptr<SparseVoxelOctree> m_SVO;


    public:

        /**
         * GETTERS AND SETTERS
         */

        /*Grid Size*/
        static inline auto GetGridSize() -> unsigned __int16 { return m_GridSize;}
        static inline auto SetGridSize(unsigned __int16 GGridSize) -> void {m_GridSize = GGridSize;}

    };

}
#endif
