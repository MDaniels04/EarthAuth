#include <pch.h>
#include "include/EarthAuth.h"

#include <pch.h>

#include "PerlinNoise.hpp"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

using namespace LabRat;

int main()
{

    /*Create our application as a (templated) singleton*/
    std::unique_ptr<EarthAuth> EarthAuthApp = std::make_unique<EarthAuth>(ERenderingLibrary::ERL_OpenGL);

    if (!EarthAuthApp.get())
    {
        Utils::Debug::PrintDebugText("Could not create Earth Auth",  Utils::EDMT_Error);
        return -1;
    }


    /*If we do not have the main window initialised, there is a problem!*/
    if (!EarthAuthApp.get()->InitialiseApplication(480, 480,  "Earth Auth"))
    {
        Utils::Debug::PrintDebugText("Could not initialise Earth Auth application",  Utils::EDMT_Error);
        return -1;
    }

    while (EarthAuthApp.get()->GetShouldUpdate())
    {
        EarthAuthApp.get()->UpdateApplication();
    }

    //TODO PORT ALL OF THIS STUFF TO A GAME MANAGER


}