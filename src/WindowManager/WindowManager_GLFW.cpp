#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

#define GLFW_INCLUDE_NONE //Ensures no header conflicts in GLFW w/ GLAD
#include <glad/gl.h> //GLAD
#include <GLFW/glfw3.h> //GLFW

namespace EarthAuth {

    //Actual definition of the deleter - ensure we are using GLFWs window deletion func
    void GLFWwindow_DEL::operator() (GLFWwindow* win)
    {
        glfwDestroyWindow(win);
    }

    WindowManager_GLFW::WindowManager_GLFW()
    {
        //Error callback setup
        glfwSetErrorCallback(ErrorCallback);
    }

    WindowManager_GLFW::~WindowManager_GLFW()
    {
        //Terminate glfw (if we have not already done so
        glfwTerminate();
    }

    WindowManager_GLFW::WindowManager_GLFW(unsigned int MainWindowWidth, unsigned int MainWindowHeight, const char* MainWindowTitle)
    : WindowManager_Base::WindowManager_Base(MainWindowWidth, MainWindowHeight, MainWindowTitle)
    {
        Utils::Debug::PrintDebugText("Hello World!", Utils::EDebugMessageType::EDMT_Error);
        //Error callback setup
        glfwSetErrorCallback(ErrorCallback);
    }

    auto WindowManager_GLFW::InitialiseMainWindow() -> const bool
    {
        //Initialise glfw, returning if we are unable to do so
        if (!glfwInit())
        {
            //TODO Debug messaging functionality in utils would be handy
            glfwTerminate();
            return false;
        }

        //Setting the minimum required versions for OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        //TODO this line helps add mac suppourt, but will tie us to OpenGL - this boiler plate needs to get off the ground, then I need to think abt how to get around hard coding OpenGL as opposed to Vulkan, e.g.
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



        m_MainWindow = std::unique_ptr<GLFWwindow, GLFWwindow_DEL>(glfwCreateWindow(m_MainWindowWidth, m_MainWindowHeight, m_MainWindowTitle.c_str(), NULL, NULL));

        if (!(m_MainWindow.get()))
        {
            std::cout << "m_MainWindow is null\n";
            glfwTerminate();
            return false;
        }

        std::cout << "m_MainWindow is not null, loading...\n";

        glfwMakeContextCurrent(m_MainWindow.get());
        gladLoadGL(glfwGetProcAddress);


        return true;
    }

    auto WindowManager_GLFW::UpdateMainWindow() -> const unsigned int
    {
        if (glfwWindowShouldClose(m_MainWindow.get()))
        {
            glfwDestroyWindow(m_MainWindow.get());
            return 1;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_MainWindow.get());
        glfwPollEvents();

        return 0;
    }


    auto WindowManager_GLFW::ErrorCallback(int Err, const char* Desc)-> void
    {
        //TODO that utils library with some debug printing functionality would help a lot here...
        std::cout << "Window Error: GLFW \nError Code: " << std::to_string(Err) << "\nDescription: " << Desc << "\n";
    }

}
