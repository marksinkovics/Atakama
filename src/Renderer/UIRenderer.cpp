#include "UIRenderer.hpp"

#include "Engine/Scene.hpp"
#include "Perf/PerfMonitor.hpp"
#include "Engine/Texture.hpp"
#include "Engine/FrameBuffer.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

void UIRenderer::Draw(Ref<Scene>& scene, Ref<PerfMonitor>& perfMonitor, Ref<FrameBuffer>& frameBuffer)
{
    
    ImGui::Begin("Depth window");
    ImVec2 sceneWindowSize= ImGui::GetContentRegionAvail();
//    ImDrawList* drawList = ImGui::GetWindowDrawList();
    {
        ImVec2 wSize = ImGui::GetContentRegionAvail();
        ImGui::Image((ImTextureID)frameBuffer->GetDepthTexture()->GetId(), wSize, ImVec2(0, 1), ImVec2(1, 0));
    //    drawList->AddImage(
    //        (void *)frameBuffer->GetDepthTexture()->GetId(),
    //        ImVec2(ImGui::GetCursorScreenPos()),
    //        ImVec2(ImGui::GetCursorScreenPos().x + frameBuffer->GetWidth()/2, ImGui::GetCursorScreenPos().y + frameBuffer->GetHeight()/2), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }
    
    {
        ImGui::Begin("Scene window");
        ImVec2 wSize = ImGui::GetContentRegionAvail();
        ImGui::Image((ImTextureID)frameBuffer->GetColorTexture()->GetId(), wSize, ImVec2(0, 1), ImVec2(1, 0));
    //    ImGui::GetWindowDrawList()->AddImage(
    //        (void *)frameBuffer->GetColorTexture()->GetId(), ImVec2(ImGui::GetCursorScreenPos()),
    //        ImVec2(ImGui::GetCursorScreenPos().x + frameBuffer->GetWidth()/2, ImGui::GetCursorScreenPos().y + frameBuffer->GetHeight()/2), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    ImGui::Begin("ImGui Window");
    ImGui::Text("CPU time: %f ms", perfMonitor->GetCPUTime());
    ImGui::Text("GPU time: %f ms", perfMonitor->GetGPUTime());
    ImGui::DragFloat3("Light position", (float*)&scene->GetLight()->GetPositionRef(), 0.01);
    ImGui::ColorEdit3("Light color", (float*)&scene->GetLight()->GetColorRef());
    ImGui::Text("Scene window size: (%f, %f)", sceneWindowSize.x, sceneWindowSize.y);
    ImGui::End();
    
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
