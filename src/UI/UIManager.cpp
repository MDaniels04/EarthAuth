#include "EarthAuth/UI/UIManager.h"

// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"



#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

#include "GLFW/glfw3.h"

namespace LabRat {

    UIManager::UIManager()
    {

    }


    UIManager::~UIManager()
    {
        ShutdownUI();
    }

    auto UIManager::InitUI(GLFWwindow* GivenWindow) -> const bool
    {
        // IMGUI_CHECKVERSION();
        // ImGui::CreateContext();
        // ImGuiIO &io = ImGui::GetIO();
        //
        // ImGui_ImplGlfw_InitForOpenGL(GivenWindow, true);
        // //TEMP can we get away without specifying a glsl version?
        // ImGui_ImplOpenGL3_Init();
        // //And dark mode, because of course
        // ImGui::StyleColorsDark();

        return true;
    }

    auto UIManager::UpdateUI() -> void
    {
        //Defining the contents of the UI window
        // ImGui::Begin("Interface");
        // ImGui::Button("Generate Terrain");
        // ImGui::End();
        //
        // //Rendering of the UI
        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    auto UIManager::ShutdownUI() -> void
    {
        // ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        // ImGui::DestroyContext();
    }
}