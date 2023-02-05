#include "SandboxApplication.hpp"

#include "Layer/StatsLayer.hpp"

#include <Atakama/Engine/RenderPass/DebugRenderPass.hpp>
#include <Atakama/Engine/RenderPass/DepthViewRenderPass.hpp>
#include <Atakama/Engine/RenderPass/OutlineRenderPass.hpp>

namespace Atakama::Sandbox
{

SandboxApplication::SandboxApplication()
: Application()
{
    AddLayer(new StatsLayer());

    m_Engine->UpdateRenderingViewportSize(m_Window->GetFrameBufferSize());

    m_Engine->GetDebugRenderPass()->SetEnable(false);
    m_Engine->GetDepthViewRenderPass()->SetEnable(false);
    m_Engine->GetOutlineRenderPass()->SetEnable(false);
}

}
