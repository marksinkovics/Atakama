#ifndef SCREEN_RENDERER_HPP
#define SCREEN_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

#include "Engine/FrameBuffer.hpp"

namespace OGLSample
{

class ScreenRenderer: public Renderer
{
public:
    virtual ~ScreenRenderer() = default;
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    void StartRecord();
    void StopRecord();
    void Draw();
    void Resize(uint32_t width, uint32_t height);
    glm::uvec2 GetSize();

    Ref<FrameBuffer>& GetFrameBuffer();
private:
    Ref<FrameBuffer> m_FrameBuffer;
    Ref<Mesh> m_QuadMesh;
};

}

#endif
