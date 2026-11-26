
#ifndef EARTHAUTH_APPMANAGER_H
#define EARTHAUTH_APPMANAGER_H

#pragma once

#include <pch.h>



/*Following Meyer's singleton design: https://www.geeksforgeeks.org/cpp/implementation-of-singleton-class-in-cpp/ */

namespace LabRat
{

    /*The rendering library (& consequently window management library) we want to use with our application*/
    enum ERenderingLibrary
    {
        ERL_OpenGL /*Default (and likely only for the scope of this project) library used for rendering. I may go back and add Vulkan if I have time later*/
    };

    class WindowManager_Base;

    class UIManager;
    /*
     * An application handles all of the "engine" logic needed for an app.
     * It has a window manager, render manager [...TODO EXPAND]
     *
     *They are intended to be used as if they were singletons - I have seen a lot of
     *stuff online denouncing singletons, and they raise decent points - it is a pattern i will look into properly
     *beyond the feasibility demo.
     */
    class Application
    {
    public:


        /*Default constructor for app manager*/
        Application();

        /*Constructor specicifying the rendering library we want to use, and hence the type of window and render manager that will be initialised*/
        Application(ERenderingLibrary RenderingLibrary);

        /*TODO is this useful static?*/
        /*Get if we should keep updating the app via the main loop*/
        auto GetShouldUpdate() -> const bool;

        /*Default destructor - needs to be public for unique ptr use*/
        ~Application();

        /**
        * FUNCTIONS
        */

        /*Initialise application and its components*/
        virtual auto InitialiseApplication(const unsigned int WindowWidth, const unsigned int WindowHeight, const char* WindowName) -> const bool;

        /*Our applications main update loop - all manager specific functionality will happen within this loop.*/
        virtual auto UpdateApplication() -> const int;

    protected:




        /**
         * VARIABLES
         */


        /*This application's  window manager
         *- handles library specific handling of our window operations, like opening, updating, getting inputs and closing windows
         *
         */
        std::unique_ptr<WindowManager_Base> m_WindowManager;

        /*boolean keeping track if our window should update loop or not - essentially, only false if we should close*/
        bool m_bShouldUpdate;
    };


}

#endif //BSDCOUNTER_TXT_APPMANAGER_H
