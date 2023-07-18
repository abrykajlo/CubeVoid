#include "editor.h"

#include <render/components.h>
#include <simulation/components.h>

#include <SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <glad/gl.h>

using namespace cv::editor;

Editor::Editor() {}

Editor::~Editor() {}

int
Editor::Init()
{
    InitRendering();
    InitScene();
    InitImGui();
    return 0;
}

int
Editor::Quit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    SDL_Quit();

    return 0;
}

int
Editor::Run()
{
    bool done = false;
    while (!done) {
        m_clock.Start();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }

            ImGui_ImplSDL2_ProcessEvent(&event);
        }

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        EditorWindow();
        ImGui::EndFrame();
        Render();
        m_clock.Stop();
    }

    return 0;
}

void
Editor::EditorWindow()
{
    ImGui::Begin("Editor");
    const auto& contentSize = ImGui::GetContentRegionAvail();
    render::Rect rect(contentSize.x, contentSize.y);
    m_texture->SetRect(rect);
    if (m_renderBuffer->GetRect() != rect) {
        m_renderBuffer->SetRect(rect);
        m_frameBuffer->Delete();
        m_frameBuffer->Gen();
        m_frameBuffer->AttachTexture(*m_texture);
        m_frameBuffer->AttachDepthBuffer(*m_renderBuffer);
    }
    m_frameBuffer->Bind();
    m_renderManager->Render(m_clock.GetTimeDelta());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::Image((void*)m_texture->GetId(), contentSize);
    ImGui::End();
}

int
cv::editor::Editor::InitRendering()
{
    if (m_window.Init() < 0) {
        return -1;
    }

    m_context = std::make_unique<render::Context>(m_window, 4, 5);
    if (!m_context->Valid()) {
        return -1;
    }

    m_renderManager =
        std::make_unique<render::RenderManager>(m_window, m_entityRegistry);
    if (m_renderManager->Init() < 0) {
        return -1;
    }
    m_frameBuffer = std::make_unique<render::gl::FrameBuffer>();
    m_texture = std::make_unique<render::gl::Texture>();
    m_renderBuffer = std::make_unique<render::gl::RenderBuffer>();
    m_frameBuffer->AttachTexture(*m_texture);
    m_frameBuffer->AttachDepthBuffer(*m_renderBuffer);

    SDL_GL_SetSwapInterval(1);
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        return -1;
    }

    return 0;
}

int
cv::editor::Editor::InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    if (!ImGui_ImplSDL2_InitForOpenGL(m_window.Get(), m_context->Get())) {
        return -1;
    }

    if (!ImGui_ImplOpenGL3_Init()) {
        return -1;
    }

    return 0;
}

void
cv::editor::Editor::InitScene()
{
    // setup camera
    glm::vec3 eye(2, 2, 0);
    glm::vec3 at(0, 0, 0);
    entt::handle camHandle(m_entityRegistry, m_entityRegistry.create());
    camHandle.emplace<cv::render::component::MainCamera>(
        glm::radians(45.f), 0.1f, 100.f);

    camHandle.emplace<cv::sim::component::Position>(eye);

    camHandle.emplace<cv::sim::component::Rotation>(
        glm::quatLookAt(glm::normalize(at - eye), glm::vec3(0, 1, 0)));

    // setup torus
    entt::handle torus(m_entityRegistry, m_entityRegistry.create());

    cv::render::component::PBRMaterial material;
    material.Color = vec3(1.0, 0.0, 0.0);
    material.Metal = false;
    material.Roughness = 0.25;
    torus.emplace<cv::render::component::PBRMaterial>(material);

    cv::render::Mesh mesh;
    cv::render::MakeTorus(mesh, 0.3f, 1.f, 50, 100);
    mesh.Init();
    torus.emplace<cv::render::component::Mesh>(mesh);

    // setup lighting
    entt::handle lightEntity1(m_entityRegistry, m_entityRegistry.create());

    cv::render::component::PBRLight light1;
    light1.L = vec3(0.2);

    lightEntity1.emplace<cv::render::component::PBRLight>(light1);
    lightEntity1.emplace<cv::sim::component::Position>(vec3(-2, 0, 0));
}

void
Editor::Render()
{
    const ImGuiIO& io = ImGui::GetIO();

    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // render additional platform windows
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

    m_window.Swap();
}
