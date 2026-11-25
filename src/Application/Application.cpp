#include "EarthAuth/Application/Application.h"

#include "EarthAuth/WindowManager/WindowManager_Base.h"
#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

namespace LabRat {
    //Initialilse window manager to null if nothing passed along
    Application::Application() : m_WindowManager(nullptr), m_bShouldUpdate(false)
    {
    }

    Application::Application(ERenderingLibrary RenderingLibrary) : m_bShouldUpdate(false)
    {
        switch (RenderingLibrary)
        {
            //Window manager of type GLFW, render manager of type Open GL
            case ERenderingLibrary::ERL_OpenGL:
                m_WindowManager = std::make_unique<WindowManager_GLFW>(480, 480, "Window");
                break;
            default:
                m_WindowManager = std::make_unique<WindowManager_GLFW>(480, 480, "Window");
                break;
        }


    }

    Application::~Application()
    {
        // if (m_WindowManager.get())
        //     m_WindowManager.get()->ShutdownWindow();
    }

    // template <class T>
    // auto Application::Singleton(ERenderingLibrary RL) -> T&
    // {
    //     /*Create our singleton - template will be the App subclass. TODO is this good practice?*/
    //     static std::unique_ptr<T> App (new T(RL));
    //     return *App;
    // }

    auto Application::GetShouldUpdate() -> const bool
    {
        return m_bShouldUpdate;
    }

    //NOTE TO ANY PROSPECTIVE APPLICATION PROGRAMMERS (if I make this a fully fleged engine one day) Get Should Update is a check that
    //should be ran in ur main.cpp
    auto Application::UpdateApplication() -> const int
    {

        if (m_WindowManager.get()->GetShouldWindowUpdate())
        {
            m_WindowManager->UpdateMainWindow();
            return 0; //Return 0 - all good, no problems
        }

        //Stop updating!
        m_bShouldUpdate = false;
        return 1; //1 - ended (normal - will later expand this to denote errors)

    }

    auto Application::InitialiseApplication(const unsigned int WindowWidth, const unsigned int WindowHeight, const char* WindowName) -> const bool
    {

        if (!m_WindowManager.get())
        {
            Utils::Debug::PrintDebugText("Application window manager is null", Utils::EDebugMessageType::EDMT_Error);
        }

        m_WindowManager->InitialiseMainWindow();


        //At the end of initialise, if we get to this point it is all systems go, we mark the app as being able to update now
        m_bShouldUpdate = true;

        return true;
    }

}