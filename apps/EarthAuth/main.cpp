#include <pch.h>

#include <PerlinNoise.hpp>

#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

using namespace EarthAuth;

int main()
{
    std::unique_ptr<WindowManager_GLFW> WindowManager = std::make_unique<WindowManager_GLFW>(480,480, "Earth Auth");


    if (!WindowManager.get()->InitialiseMainWindow())
        std::cout << "Damn\n";

    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    //Perlis noise example thing...
    const siv::PerlinNoise::seed_type seed = 123456u; //TODO swap this out for time
    const siv::PerlinNoise perlin{ seed };

    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            const double noise = perlin.octave2D_01((x * 0.01), (y * 0.01), 4);

            std::cout << noise << '\t';
        }

        std::cout << '\n';
    }

    bool bMainLoop = true;

    //TODO PORT ALL OF THIS STUFF TO A GAME MANAGER
    while (bMainLoop)
    {
        const int WinUpdateOutput = WindowManager->UpdateMainWindow();

        //i.e.: if something was out of the ordinary
        if (WinUpdateOutput != 0)
        {
            std::cout << "EA: Window update exited with code: " << WinUpdateOutput << '\n';
        }
    }
}