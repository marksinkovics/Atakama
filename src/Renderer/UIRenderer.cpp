#include "UIRenderer.hpp"

#include "Engine/Scene.hpp"
#include "Perf/PerfMonitor.hpp"

namespace OGLSample
{

void UIRenderer::Init(Ref<Window>& window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void UIRenderer::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void UIRenderer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIRenderer::Draw(Ref<Scene>& scene, Ref<PerfMonitor>& perfMonitor)
{
    ImGui::Begin("ImGui Window");
    ImGui::Text("CPU time: %f ms", perfMonitor->GetCPUTime());
    ImGui::Text("GPU time: %f ms", perfMonitor->GetGPUTime());

    ImGui::DragFloat3("Light position", (float*)&scene->GetLight()->GetPositionRef(), 0.01);
    ImGui::ColorEdit3("Light color", (float*)&scene->GetLight()->GetColorRef());
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
