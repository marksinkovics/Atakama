#ifndef SCREEN_RENDERER_HPP
#define SCREEN_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

#include "Engine/FrameBuffer.hpp"

namespace OGLSample
{

class WindowFrameBufferResizeEvent;

class ScreenRenderer: public Renderer
{
public:
    virtual ~ScreenRenderer() = default;
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    bool OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event);
    void StartRecord();
    void StopRecord();
    void Draw(float time, glm::vec2 frameSize);
private:
    Ref<FrameBuffer> m_FrameBuffer;
    Ref<Mesh> m_QuadMesh;
};

}

#endif
