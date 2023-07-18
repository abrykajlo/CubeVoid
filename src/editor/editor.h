#pragma once

#include <engine/clock.h>
#include <render/gl/frame_buffer.h>
#include <render/render.h>
#include <render/gl/render_buffer.h>
#include <render/gl/texture.h>
#include <render/window.h>

#include <entt/entt.hpp>
#include <SDL.h>

#include <memory>

namespace cv {
namespace editor {
class Editor
{
  public:
    Editor();
    ~Editor();

    int Init();
    int Quit();
    int Run();

  private:
    void Render();
    void EditorWindow();
    int InitRendering();
    int InitImGui();
    void InitScene();

    render::Window m_window;
    entt::registry m_entityRegistry;
    std::unique_ptr<render::Context> m_context;
    std::unique_ptr<render::RenderManager> m_renderManager;
    engine::Clock m_clock;
    std::unique_ptr<render::gl::Texture> m_texture;
    std::unique_ptr<render::gl::FrameBuffer> m_frameBuffer;
    std::unique_ptr<render::gl::RenderBuffer> m_renderBuffer;
};
}
}