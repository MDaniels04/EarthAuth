#include "EarthAuth/Application/Application.h"

#include "EarthAuth/WindowManager/WindowManager_Base.h"
#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

namespace LabRat
{
    //Initialilse window manager to null if nothing passed along
    Application::Application() : m_WindowManager(nullptr)
    {
    }

    Application::Application(ERenderingLibrary RenderingLibrary)
    {
        switch (RenderingLibrary)
        {
            //Window manager of type GLFW, render manager of type Open GL
            case ERenderingLibrary::ERL_OpenGL:
                m_WindowManager = std::unique_ptr<WindowManager_GLFW>();
                break;
            default:
                m_WindowManager = std::unique_ptr<WindowManager_GLFW>(new WindowManager_GLFW());
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


    auto Application::InitialiseApplication() -> const bool
    {

        if (!m_WindowManager.get())
        {
            Utils::Debug::PrintDebugText("Application window manager is null", Utils::EDebugMessageType::EDMT_Error);
        }

        m_WindowManager->InitialiseMainWindow();

        return true;
    }

}