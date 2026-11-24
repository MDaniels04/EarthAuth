//
// Created by Morga on 17/11/2026.
//


#ifndef EARTHAUTH_WINDOWMANAGER_H
#define EARTHAUTH_WINDOWMANAGER_H

#pragma once

#include <pch.h>

#include "WindowManager_Base.h"



/*Forward decl of glfdfw structs*/
struct GLFWwindow;
struct GLFWmonitor;

/*Window manager part of earth auth namespace*/
namespace EarthAuth {


    /*Forward decl of helper structs; deleters for GLFW objects for the unique ptr member vars*/
    /*Thank you to this stack overflow bit for the fix https://stackoverflow.com/questions/35793672/use-unique-ptr-with-glfwwindow*/
    struct GLFWwindow_DEL
    {
        void operator() (GLFWwindow* win);
    };

    /*
    * Our window manager class handles the instantiation of the window, window events, and inputs in a platform abbstracted manner.
    */
    class WindowManager_GLFW : public WindowManager_Base
    {

    public:

        /*Default constructor, set all our vars to null*/
        WindowManager_GLFW();

        /*Constructor, initialise values as the base constructor, and set the glfw error callback up*/
        WindowManager_GLFW(const unsigned int width, const unsigned int height, const char* title);

        /*Default destructor*/
        ~WindowManager_GLFW();

        /*
        * //////////
        * FUNCTIONS
        * //////////
        */


        /*
         * GLFW override of initialise main window with library specific implementation.
         * Returns TRUE / FALSE based on initialisation success
         */
        virtual auto InitialiseMainWindow() -> const bool override;

        /*
         * GLFW override of update main window with library specific implementation.
         * Returns an uint describing the success or errors that came up during the update
         * (i.e.: 0 -> updated, 1... -> update problem, number describing)
         */
        virtual auto UpdateMainWindow() -> const unsigned int override;


    private:

        /*Error  callback function, bound to glfwSetErrorCallback*/
        static auto ErrorCallback(int Err, const char* Desc) -> void;

        /*Main GLFW window ptr*/
        std::unique_ptr<GLFWwindow, GLFWwindow_DEL> m_MainWindow;

    };
}
#endif
