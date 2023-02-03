#include "EditorRenderPass.hpp"

#include "Perf/PerfMonitor.hpp"

namespace Atakama
{

EditorRenderPass::EditorRenderPass(Ref<RenderSystem> renderSystem, Ref<PerfMonitor>& perfMonitor)
: RenderPass(renderSystem), m_perfMonitor(perfMonitor)
{
    
}

}
