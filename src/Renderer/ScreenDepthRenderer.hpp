#ifndef SCREEN_DEPTH_RENDERER_HPP
#define SCREEN_DEPTH_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

#include "Engine/FrameBuffer.hpp"

namespace OGLSample
{

class ScreenDepthRenderer: public Renderer
{
public:
    virtual ~ScreenDepthRenderer() = default;
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    void StartRecord();
    void StopRecord();
    void Draw(Ref<Texture> depthTexture);
    void Resize(uint32_t width, uint32_t height);
    glm::uvec2 GetSize();

    Ref<FrameBuffer>& GetFrameBuffer();
private:
    Ref<FrameBuffer> m_FrameBuffer;
    Ref<Mesh> m_QuadMesh;
};

}

#endif
