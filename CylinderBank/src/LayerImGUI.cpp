#include "CylinderBank_pch.hpp"

#include "CylinderBank/Layers/LayerImGUI.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "CylinderBank/Systems/Application.hpp"
#include "CylinderBank/util.hpp"
#include "CylinderBank/Input/keycodes.hpp"

#include<GLFW/glfw3.h>

namespace CylinderBank
{
    LayerImGUI * LayerImGUI::instance = nullptr;

    LayerImGUI::LayerImGUI() :
    Layer("ImGUI Layer")
    {
        CB_ASSERT_CORE(instance == nullptr,
                       "There may only be one ImGUI layer.");
        instance = this;
    }

    LayerImGUI::~LayerImGUI() 
    {
    }

    void LayerImGUI::on_push() 
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        Application& app = Application::get_instance();
        GLFWwindow* window =
            static_cast<GLFWwindow*>(app.get_window().get_native_window());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void LayerImGUI::on_pop() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void LayerImGUI::begin_render()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void LayerImGUI::complete_render()
    {
        ImGuiIO     &io  = ImGui::GetIO();
        Application &app = Application::get_instance();
        io.DisplaySize   = ImVec2((float)app.get_window().get_width(),
                                  (float)app.get_window().get_height());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void LayerImGUI::imgui_draw()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
}