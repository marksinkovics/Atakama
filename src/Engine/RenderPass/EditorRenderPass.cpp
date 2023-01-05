#include "EditorRenderPass.hpp"

#include "Perf/PerfMonitor.hpp"

namespace OGLSample
{

EditorRenderPass::EditorRenderPass(Ref<RenderSystem> renderSystem, Ref<PerfMonitor>& perfMonitor)
: RenderPass(renderSystem), m_perfMonitor(perfMonitor)
{
    
}

}
