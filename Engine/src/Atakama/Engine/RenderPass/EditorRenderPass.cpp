#include "EditorRenderPass.hpp"

#include "Atakama/Core/Profiler.hpp"

namespace Atakama
{

EditorRenderPass::EditorRenderPass(Ref<RenderSystem> renderSystem, Ref<Profiler>& profiler)
: RenderPass(renderSystem), m_Profiler(profiler)
{
    
}

}
