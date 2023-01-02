#include "UIRenderer.hpp"

#include "Engine/Engine.hpp"
#include "Engine/Scene.hpp"
#include "Perf/PerfMonitor.hpp"
#include "Engine/Texture.hpp"
#include "Engine/FrameBuffer.hpp"
#include "FileSystem.hpp"
#include "Window.hpp"
#include "Application.hpp"

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

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
    if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f)
    {
        Ref<ScreenRenderer> screenRenderer = g_RuntimeGlobalContext.m_Engine->GetScreenRenderer();
        if (screenRenderer->GetSize() != m_ViewportSize)
        {
            screenRenderer->Resize(m_ViewportSize.x, m_ViewportSize.y);
        }

        Ref<ScreenDepthRenderer> screenDepthRenderer = g_RuntimeGlobalContext.m_Engine->GetScreenDepthRenderer();
        if (screenDepthRenderer->GetSize() != m_ViewportSize)
        {
            screenDepthRenderer->Resize(m_ViewportSize.x, m_ViewportSize.y);
        }


    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIRenderer::Draw(Ref<Scene>& scene, Ref<PerfMonitor>& perfMonitor, Ref<Texture> colorTexture, Ref<Texture> depthTexture)
{
    static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
          const ImGuiViewport *viewport = ImGui::GetMainViewport();
          ImGui::SetNextWindowPos(viewport->WorkPos);
          ImGui::SetNextWindowSize(viewport->WorkSize);
          ImGui::SetNextWindowViewport(viewport->ID);
          ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
          ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
          window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
          window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
          dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
          window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
          ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
          ImGui::PopStyleVar();

        if (opt_fullscreen)
          ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
          ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
          ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        io.ConfigWindowsMoveFromTitleBarOnly = true;

        style.WindowMinSize.x = minWinSizeX;
    }

    ImGui::ShowDemoWindow();

#if 1
    {
        ImGui::Begin("Depth window");
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImVec2 wSize = ImGui::GetContentRegionAvail();
        ImGui::Image(reinterpret_cast<ImTextureID>(depthTexture->GetId()), wSize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::PopStyleVar();
        ImGui::End();
    }
#endif
    {
        ImGui::Begin("Scene window");
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsMouseHoveringRect(vMin, vMax);
        g_RuntimeGlobalContext.m_Application->BlockEvent(!(m_ViewportFocused && m_ViewportHovered));
//        ImGui::GetForegroundDrawList()->AddRect( vMin, vMax, IM_COL32( 255, 255, 0, 255 ) );

        ImVec2 wSize = ImGui::GetContentRegionAvail();
        float scale = ImGui::GetMainViewport()->DpiScale;
        m_ViewportSize = { wSize.x * scale, wSize.y * scale };

        ImGui::Image(reinterpret_cast<ImTextureID>(colorTexture->GetId()), wSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::PopStyleVar();
        ImGui::End();
    }

    {
        ImGui::Begin("ImGui Window");
        ImGui::Text("CPU time: %f ms", perfMonitor->GetCPUTime());
        ImGui::Text("GPU time: %f ms", perfMonitor->GetGPUTime());
        ImGui::Text("AVG %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Viewport size %s", glm::to_string(m_ViewportSize).c_str());
        ImGui::DragFloat3("Light position", (float*)&scene->GetLight()->GetPositionRef(), 0.01);
        ImGui::ColorEdit3("Light color", (float*)&scene->GetLight()->GetColorRef());
        ImGui::End();
    }



    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
