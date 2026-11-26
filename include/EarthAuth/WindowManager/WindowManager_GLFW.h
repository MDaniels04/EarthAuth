//
// Created by Morga on 17/11/2026.
//


#ifndef EARTHAUTH_WINDOWMANAGER_H
#define EARTHAUTH_WINDOWMANAGER_H

#pragma once

#include <pch.h>
#include <glm/glm.hpp>
#include "WindowManager_Base.h"



/*Forward decl of glfdfw structs*/
struct GLFWwindow;
struct GLFWmonitor;


/*Window manager part of earth auth namespace*/
namespace LabRat {

    /*Forward declaring render manager class*/
    class RenderManager_GL;
    class UIManager;

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

        /*Key callback function, bound to glfwSetKeyCallback*/
        static auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;

        /*Update the position we are viewing from based on what inputs are being held*/
        auto UpdateMovement(float DeltaTime) -> void;

        static auto UpdateVectors() -> void;

        /*Callback function for mouse movement - i.e.: looking around WHEN HOLDING THE RIGHT MOUSE BUTTON*/
        static auto MouseCallback(GLFWwindow* window, double XPos, double YPos) -> void;


        /*Tracks the state of our movement keys - a rudimentary fix to allow multiple inputs in the shadow of a proper input management system*/
        static inline std::unordered_map<unsigned int, bool> m_KeyStateTracker = {};

        /*Main GLFW window ptr*/
        std::unique_ptr<GLFWwindow, GLFWwindow_DEL> m_MainWindow;

        /*FOR NOW all GLFW windows will just have a GL renderer. Eventually (as in like august) I might make a vulkan renderer version*/
        std::unique_ptr<RenderManager_GL> m_RenderManager;

        /*Static double storing delta time - can be used anywhere as a result of this*/
        static inline double m_DeltaTime = 0.f;

        /*The time elapsed since the last frame in the window happened - used for DeltaTime calculations*/
        double m_LastFrameTime;

        /*EXTREMELY TEMP: WE ARE GOING TO HAVE CAMERA FUNCTIONALITY IN THE MAIN WINDOW FOR THE TIME BEING: THERE IS NO POINT IN IT BEING GOOD YET
         * FD IS NOT ASSESSED TOO MUCH ON THE SOFTWARE ARCH AND WE JUST NEED STUFF OF THE GROUND
         * TODO A CAMERA CLASS FOR THESE
         */

        /*How quick do we want to move? Temporarily here*/
        static inline float m_MoveSpeed = 0.1f;

        //TEMP This is public so we can access it from our renderer without having to messily parameterise it
        /*Position we want to view the world from*/
        static inline glm::vec3 m_ViewPosition = glm::vec3(-4.f,3.f,3.f);

        /*Direction view is pointing in - i.e. the forward vector*/
        static inline glm::vec3 m_ViewDirection = glm::vec3(1.f, 0.f, 0.f);

        /*Where is "up" for the view?*/
        static inline glm::vec3 m_ViewUp = glm::vec3(0.f, 1.f, 0.f);

        /*Rotation (in radians) of the view*/
        static inline glm::vec3 m_ViewRotation = glm::vec3(0.f,0.f,0.f);

        static inline glm::vec3 m_ViewRight = glm::normalize(glm::cross(m_ViewDirection, glm::vec3(0,1,0)));

        /*Are we holding the corresponding key that should convert mouse input to rotating the camera*/
        static inline bool m_bMouseLookMode = false;

        /*The Mouse position last update - used for calculating the mouse delta for rotating the camera */
        static inline glm::vec2 m_LastMousePos = glm::vec2(0.f);

        /*Speed with which camera should rotate*/
        static inline float m_LookSpeed = 0.5f;

        /*Static var for gl version - used to be passsed  to our UI manager*/
        static char* m_GLVersion;

        /*PTR to UI manager - handled in our main step too...*/
        std::unique_ptr<UIManager> m_UIManager;

    public:

        /*GETTERS N SETTERS*/

        /*View Position*/
        static inline auto GetViewPosition() -> glm::vec3 { return m_ViewPosition;}

        /*View direction*/
        static inline auto GetViewDirection() -> glm::vec3 { return m_ViewDirection;}

        /*View Up*/
        static inline auto GetViewUp() -> glm::vec3 { return m_ViewUp; }

        /*Delta Time*/
        static inline auto GetDeltaTime() -> double { return m_DeltaTime;}

        /*TEMP main window getter to allow ImGUI to establish a context were using */
        inline auto GetMainWindow() -> GLFWwindow* { return m_MainWindow.get();}

    };
}
#endif
