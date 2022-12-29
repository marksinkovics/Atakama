#ifndef SCREEN_DEPTH_RENDERER_HPP
#define SCREEN_DEPTH_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

#include "Engine/FrameBuffer.hpp"

namespace OGLSample
{

class WindowFrameBufferResizeEvent;

class ScreenDepthRenderer: public Renderer
{
public:
    virtual ~ScreenDepthRenderer() = default;
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    bool OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event);
    void StartRecord();
    void StopRecord();
    void Draw(float time, glm::vec2 frameSize, Ref<Texture> depthTexture);
    
    Ref<FrameBuffer>& GetFrameBuffer();
private:
    Ref<FrameBuffer> m_FrameBuffer;
    Ref<Mesh> m_QuadMesh;
};

}

#endif
