#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

#define GLFW_INCLUDE_NONE //Ensures no header conflicts in GLFW w/ GLAD
#include <glad/gl.h> //GLAD
#include <GLFW/glfw3.h> //GLFW
#include "EarthAuth/UI/UIManager.h"

#include "EarthAuth/Renderer/RenderManager_GL.h"

//Our render manager; OpenGL

namespace LabRat
{
    //Actual definition of the deleter - ensure we are using GLFWs window deletion func
    void GLFWwindow_DEL::operator() (GLFWwindow* win)
    {
        glfwDestroyWindow(win);
    }

    WindowManager_GLFW::WindowManager_GLFW() : m_RenderManager(nullptr)//, m_LastFrameTime(0.0f)
    {
        //Error callback setup
        glfwSetErrorCallback(ErrorCallback);
        // m_MoveSpeed = 3.f;
        // m_LastFrameTime = 0.0f;
        // m_DeltaTime = 0.0f;
    }

    WindowManager_GLFW::~WindowManager_GLFW()
    {
        //Terminate glfw (if we have not already done so
        glfwTerminate();
    }

    WindowManager_GLFW::WindowManager_GLFW(const unsigned int MainWindowWidth, const unsigned int MainWindowHeight, const char* MainWindowTitle)
    : WindowManager_Base::WindowManager_Base(MainWindowWidth, MainWindowHeight, MainWindowTitle)
    {
        //Error callback setup
        glfwSetErrorCallback(ErrorCallback);
        // m_MoveSpeed = 3.f;
        // m_LastFrameTime = 0.0f;
        // m_DeltaTime = 0.0f;
    }

    auto WindowManager_GLFW::InitialiseMainWindow() -> const bool
    {

        //Initialise glfw, returning if we are unable to do so
        if (!glfwInit())
        {
            Utils::Debug::PrintDebugText("GLFW Could not be initialised", Utils::EDMT_Error);
            glfwTerminate();
            return false;
        }

        //Setting the minimum required versions for OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        //TODO this line helps add mac suppourt, but will tie us to OpenGL - this boiler plate needs to get off the ground, then I need to think abt how to get around hard coding OpenGL as opposed to Vulkan, e.g.
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_MainWindow = std::unique_ptr<GLFWwindow, GLFWwindow_DEL>(glfwCreateWindow(m_MainWindowWidth, m_MainWindowHeight, m_MainWindowTitle.c_str(), NULL, NULL));

        if (m_MainWindow.get())
        {
            std::cout << "m_MainWindow is null\n";
            glfwTerminate();
            return false;
        }


        m_UIManager = std::unique_ptr<UIManager>();
        if (!m_UIManager)
        {
            Utils::Debug::PrintDebugText("UI Manager not set up", Utils::EDMT_Error);
            return false;
        }

        m_UIManager->InitUI(m_MainWindow.get());

        std::cout << "m_MainWindow is not null, loading...\n";

        //Setup our keycallback function
        glfwSetKeyCallback(m_MainWindow.get(), KeyCallback);
        glfwSetCursorPosCallback(m_MainWindow.get(), MouseCallback);


        glfwMakeContextCurrent(m_MainWindow.get());
        //TODO If Debug precomp stuff could be set out here
        //TODO our current utils cant handle the const char* return of this...
        //std::printf("Renderer: %s\n", glGetString(GladVersion)); //So this one seems to be printing null...
        //printf( "OpenGL version supported %s.\n", glGetString( GL_VERSION ) );

        /*Now that OpenGL render context initialised, we can do this...*/

        /*Create our render manager for this window*/
        m_RenderManager = std::unique_ptr<RenderManager_GL>(new RenderManager_GL());

        if (!m_RenderManager)
        {
            Utils::Debug::PrintDebugText("Render Manager not created", Utils::EDMT_Error);
            return false;
        }

        if (!m_RenderManager->InitialiseRenderer())
        {
            Utils::Debug::PrintDebugText("Render Manager not initialised properly", Utils::EDMT_Error);
            return false;
        }

        //Setting a swap interval of 1 helps to prevent screen tearing
        glfwSwapInterval(1);

        //If we get to this point, we should be good for window updates to take place
        m_bShouldWindowUpdate = true;

        //Hotfix - we don't want to have lastframetime as 0 as that might make our first deltatime ludicrously high
        m_LastFrameTime = glfwGetTime();

        return true;
    }

    auto WindowManager_GLFW::UpdateMainWindow() -> const unsigned int
    {

        int Width, Height;

        glfwGetFramebufferSize(m_MainWindow.get(), &Width, &Height);
        const float r = Width / float(Height);

        glViewport(0,0, Width, Height);

        /*Delta time calculations*/
        //TODO MOVE THIS OUT OF HERE!
        const double CurrentFrameTime = glfwGetTime();
        m_DeltaTime = CurrentFrameTime - m_LastFrameTime;
        m_LastFrameTime -= CurrentFrameTime;

        if (glfwWindowShouldClose(m_MainWindow.get()))
        {
            glfwDestroyWindow(m_MainWindow.get());
            glfwTerminate(); //TODO is this wise to do here?
            m_bShouldWindowUpdate = false;
            return 1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        UpdateMovement(m_DeltaTime);

        m_RenderManager->UpdateRenderer(m_DeltaTime);

        glfwSwapBuffers(m_MainWindow.get());
        //TEMP - the most likely end product of this tool will only need to update when an input event is recieved.
        glfwWaitEvents();

        return 0;
    }

    auto WindowManager_GLFW::UpdateMovement(float DeltaTime) -> void
    {
        //TEMP HACKY IMPLEMENTATION
        glm::vec3 OutPos = glm::vec3(0.f);

        if (m_KeyStateTracker[GLFW_KEY_W])
            OutPos += m_ViewDirection * glm::vec3(m_MoveSpeed);
        if (m_KeyStateTracker[GLFW_KEY_S])
            OutPos += -m_ViewDirection * glm::vec3(m_MoveSpeed);
        if (m_KeyStateTracker[GLFW_KEY_A])
            OutPos += -m_ViewRight * glm::vec3(m_MoveSpeed);
        if (m_KeyStateTracker[GLFW_KEY_D])
            OutPos += m_ViewRight * glm::vec3(m_MoveSpeed);
        if (m_KeyStateTracker[GLFW_KEY_E])
            OutPos += glm::vec3(0.f,1.f,0.f) * glm::vec3(m_MoveSpeed);
        if (m_KeyStateTracker[GLFW_KEY_S])
            OutPos += -glm::vec3(0.f,1.f,0.f) * glm::vec3(m_MoveSpeed);

        m_ViewPosition += OutPos;
    }

    auto WindowManager_GLFW::UpdateVectors() -> void
    {
        m_ViewDirection = glm::vec3(
            cos(glm::radians(m_ViewRotation[2])) * cos(glm::radians(m_ViewRotation[1])),
            sin(glm::radians(m_ViewRotation[1])),
            sin(glm::radians(m_ViewRotation[2])) * cos(glm::radians(m_ViewRotation[1]))
        );

        m_ViewRight = glm::normalize(glm::cross(m_ViewDirection, glm::vec3(0.f,1.f,0.f)));

        m_ViewUp = glm::normalize(glm::cross(m_ViewRight, m_ViewDirection));
    }

    auto WindowManager_GLFW::ErrorCallback(int Err, const char* Desc)-> void
    {
        Utils::Debug::PrintDebugText("GLFW code: " + std::to_string(Err) + " description: " + Desc + "\n");
    }

    auto WindowManager_GLFW::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
    {
        if (action == GLFW_PRESS)
            m_KeyStateTracker[key] = true;
        else if (action == GLFW_RELEASE)
            m_KeyStateTracker[key] = false;

        // //VERY rudimentary input and movement system
        //  switch (key)
        //  {
        //      case GLFW_KEY_W:
        //          if (action == GLFW_PRESS)
        //             m_KeyStateTracker[key] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[key] = false;
        //          break;
        //      case GLFW_KEY_S:
        //          if (action == GLFW_PRESS)
        //              m_KeyStateTracker[GLFW_KEY_W] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[GLFW_KEY_W] = false;
        //          break;
        //      case GLFW_KEY_A:
        //          if (action == GLFW_PRESS)
        //              m_KeyStateTracker[GLFW_KEY_A] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[GLFW_KEY_A] = false;
        //          break;
        //      case GLFW_KEY_D:
        //          if (action == GLFW_PRESS)
        //              m_KeyStateTracker[GLFW_KEY_D] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[GLFW_KEY_D] = false;
        //          break;
        //      case GLFW_KEY_E:
        //          if (action == GLFW_PRESS)
        //              m_KeyStateTracker[GLFW_KEY_E] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[GLFW_KEY_E] = false;
        //          break;
        //      case GLFW_KEY_Q:
        //          if (action == GLFW_PRESS)
        //              m_KeyStateTracker[GLFW_KEY_Q] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[GLFW_KEY_Q] = false;
        //          break;
        //      case GLFW_KEY_F:
        //          if (action == GLFW_PRESS)
        //              m_KeyStateTracker[GLFW_KEY_F] = true;
        //          else if (action == GLFW_RELEASE)
        //              m_KeyStateTracker[GLFW_KEY_F] = false;
        //         break;
        //      default:
        //          break;
         //}


    }

    auto WindowManager_GLFW::MouseCallback(GLFWwindow* window, double XPos, double YPos) -> void
    {
            //FOR NOW pressing F will let you look around VS use the brush tool


        //We want to rotate the camera round to face where the mouse cursor directs it...
        glm::vec2 MouseDelta = glm::vec2(XPos, YPos) - m_LastMousePos;

        //Update last mouse pos
        m_LastMousePos = glm::vec2(XPos, YPos);

        if (!m_KeyStateTracker[GLFW_KEY_F])
            return;

        m_ViewRotation += glm::vec3(0.f, -MouseDelta.y * m_LookSpeed, MouseDelta.x * m_LookSpeed);

        m_ViewRotation = glm::vec3(m_ViewRotation.x, std::clamp(m_ViewRotation.y, -85.f, 85.f), m_ViewRotation.z);


        UpdateVectors();
    }

}
