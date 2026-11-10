#include <iostream>
#include <PerlinNoise.hpp>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main()
{
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    //Perlis noise example thing...
    const siv::PerlinNoise::seed_type seed = 123456u;
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
}