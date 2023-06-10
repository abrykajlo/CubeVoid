#pragma once

#include <engine/clock.h>
#include <render/frame_buffer.h>
#include <render/render.h>
#include <render/texture.h>
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
    void EditorWindow();
    void Render();

    render::Window m_window;
    entt::registry m_entityRegistry;
    std::unique_ptr<render::Context> m_context;
    std::unique_ptr<render::RenderManager> m_renderManager;
    engine::Clock m_clock;
    std::unique_ptr<render::Texture> m_texture;
    std::unique_ptr<render::FrameBuffer> m_frameBuffer;
};
}
}