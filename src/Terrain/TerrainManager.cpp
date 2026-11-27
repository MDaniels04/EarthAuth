#include "EarthAuth/Terrain/TerrainManager.h"

#include "PerlinNoise.hpp"
#include <glm/glm.hpp>

namespace LabRat
{
    TerrainManager::TerrainManager()
    {
    }

    TerrainManager::~TerrainManager()
    {
    }

    auto TerrainManager::GenerateTerrainFromParameters(const unsigned int Seed, const unsigned __int8 NoiseOctaves) -> bool
    {
        //See: https://github.com/Reputeless/PerlinNoise/tree/master

        unsigned int UseSeed = Seed;
        if (UseSeed == -1)
        {
            //TEMP FOR NOW WE JUST HAVE A HARDCODED SEED IN HERE
            Utils::Debug::PrintDebugText("Using randomly generated seed for terrain gen as no seed provided", Utils::EDebugMessageType::EDMT_Error);

            UseSeed = 123456u;
        }

        /*Generate some perlin noise as an initial starting point*/
        double** GenNoise = GeneratePerlinNoiseForTerrain(UseSeed, NoiseOctaves);

        /*Utilising a cellular automata-like algorithm, we want to try to consolidate this noise*/
        /*TODO COME BACK AND DO THIS, WE ARE USING RAW NOISE TO GET THIS OFF THE GROUND*/
        //this is why we wanted it as a 2d array, though, so we can ensure when building this grid, we start from the MIN point
        /*TODO a way to feed this back to ImGUI*/






        delete GenNoise;

        /*If we get to this point, we know that all is well*/
        return true;
    }


    auto TerrainManager::GeneratePerlinNoiseForTerrain(const unsigned int Seed, const unsigned __int8 NoiseOctaves) -> double**
    {
        const siv::PerlinNoise Perlin{ Seed };


        //TODO this is quite a naive implementation of storing the noise... we could hash it maybes?

        //Define the grid we wish to write this perlin noise too
        double** PerlinGrid = nullptr;

        //We need to generate 3D coordinates for the terrain over a grid
        //TODO I know it's not the most computationally demanding func but this feels horrendous



        for (int y = 0; y < m_GridSize; ++y)
            for (int x = 0; x < m_GridSize; ++x)
            {
                //The number that is generated at this point
                PerlinGrid[x][y] = Perlin.octave2D_01((x * 0.01), (y * 0.01), 6);

                //We want to take this generated noise, extrude upwards, and put it into our SVO -
            }

        //TODO so i don't think this creates a memory leak here?
        return PerlinGrid;
    }

}