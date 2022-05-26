
#include "core/hepch.h"

#include "core/ErrorHandler.h"

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleSceneManager.h"
#include "ModuleEditor.h"
#include "ModuleUserInterface.h"
#include "ModuleNavigation.h"

#include "components/ComponentCamera.h"
#include "components/ComponentTransform.h"
#include "resources/ResourceNavMesh.h"

#ifdef PLAY_BUILD
#include "ModuleInput.h"
#endif

Hachiko::ModuleRender::ModuleRender() = default;

Hachiko::ModuleRender::~ModuleRender() = default;

bool Hachiko::ModuleRender::Init()
{
    HE_LOG("Init Module render");

    CreateContext();

    RetrieveGpuInfo();
    RetrieveLibVersions();

    SetGLOptions();

    GenerateDeferredQuad();
    GenerateFrameBuffer();

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT); // Enable output callback
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(&ErrorHandler::HandleOpenGlError, nullptr); // Set the callback
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true); // Filter notifications
#endif

    fps_log = std::vector<float>(n_bins);
    ms_log = std::vector<float>(n_bins);

    return true;
}

void Hachiko::ModuleRender::GenerateFrameBuffer()
{
    glGenFramebuffers(1, &frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

    glGenTextures(1, &fb_texture);
    glBindTexture(GL_TEXTURE_2D, fb_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Depth and stencil buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_texture, 0);
    glGenRenderbuffers(1, &depth_stencil_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_buffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        HE_LOG("Error creating frame buffer");
    }

    // Generate G-Buffer and associated textures:
    g_buffer_deneme.Generate();

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Hachiko::ModuleRender::ResizeFrameBuffer(int heigth, int width) const
{
    // Frame buffer texture:
    glBindTexture(GL_TEXTURE_2D, fb_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, heigth, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    
    // Handle resizing the textures of g-buffer:
    g_buffer_deneme.Resize(heigth, width);
    
    // Unbind:
    glBindTexture(GL_TEXTURE_2D, 0);

    // TODO: Do we need this for G buffer as well? If so, do it.
    glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, heigth, width);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Hachiko::ModuleRender::ManageResolution(ComponentCamera* camera)
{
    unsigned res_x, res_y;
    camera->GetResolution(res_x, res_y);
    if (res_x != fb_height || res_y != fb_width)
    {
        ResizeFrameBuffer(res_x, res_y);
        glViewport(0, 0, res_x, res_y);
        fb_height = res_y;
        fb_width = res_x;
    }
}

void Hachiko::ModuleRender::CreateContext()
{
    HE_LOG("Creating Renderer context");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG); // enable context debug

    context = SDL_GL_CreateContext(App->window->GetWindow());
    GLenum err = glewInit();
}

void Hachiko::ModuleRender::SetGLOptions()
{
    glEnable(GL_DEPTH_TEST); // Enable depth test
    glEnable(GL_CULL_FACE); // Enable cull backward faces
    glFrontFace(GL_CCW); // Front faces will be counter clockwise
    glEnable(GL_STENCIL_TEST); // Enable stencil test
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // Only replace stencil value if stencil and depth tests pass
}

UpdateStatus Hachiko::ModuleRender::PreUpdate(const float delta)
{
    render_list.PreUpdate();

    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus Hachiko::ModuleRender::Update(const float delta)
{    
    ComponentCamera* camera = App->camera->GetRenderingCamera();
    const Scene* active_scene = App->scene_manager->GetActiveScene();   

#ifdef PLAY_BUILD
    int width, height;
    App->window->GetWindowSize(width, height);
    App->camera->OnResize(width, height);
    glViewport(0, 0, width, height);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 1, 0XFF);
    glStencilMask(0x00); // Prevent background from filling stencil
#else
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    ManageResolution(camera);
    
    //glStencilFunc(GL_ALWAYS, 1, 0XFF);
    //glStencilMask(0x00); // Prevent background from filling stencil
#endif
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);  

    if (active_scene == nullptr)
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }    

    App->program->UpdateCamera(camera);

#ifdef PLAY_BUILD
    ComponentCamera* culling = App->camera->GetRenderingCamera();
#else
    ComponentCamera* culling = active_scene->GetCullingCamera();
#endif

    const ComponentDirLight* dir_light = nullptr;
    if (!active_scene->dir_lights.empty())
        dir_light = active_scene->dir_lights[0];

    App->program->UpdateLights(dir_light, active_scene->point_lights, active_scene->spot_lights);

    Draw(App->scene_manager->GetActiveScene(), camera, culling);
    
    if (draw_navmesh)
    {
        App->navigation->DebugDraw();
    }

    App->ui->DrawUI(active_scene);

#ifndef PLAY_BUILD
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
    return UpdateStatus::UPDATE_CONTINUE;
}

void Hachiko::ModuleRender::Draw(Scene* scene, ComponentCamera* camera, 
    ComponentCamera* culling)
{
    OPTICK_CATEGORY("Draw", Optick::Category::Rendering);

    render_list.Update(culling, scene->GetQuadtree()->GetRoot());
    GameObject* selected_go = App->editor->GetSelectedGameObject();
    RenderTarget* outline_target = nullptr;
    
    Program* program = App->program->GetDeferredGeometryProgram();
    
    program->Activate();

    // Geometry pass:
    g_buffer_deneme.BindForDrawing();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Disable blending for deferred rendering as the meshes with transparent 
    // materials are gonna be rendered with forward rendering after the 
    // deferred lighting pass:
    glDisable(GL_BLEND);

    // Get opaque targets, these will be rendered in deferred rendering passes:
    std::vector<RenderTarget>& opaque_targets = render_list.GetOpaqueTargets();

    for (RenderTarget& target : opaque_targets)
    {
        target.mesh_renderer->Draw(camera, program);

        /*if (selected_go && target.game_object == selected_go)
        {
            outline_target = &target;
        }*/
    }

    Program::Deactivate();
    
    // Light Pass:
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frame_buffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use Deferred rendering lighting pass program:
    program = App->program->GetDeferredLightingProgram();
    program->Activate();

    // Bind all g-buffer textures:
    g_buffer_deneme.BindTextures();
    
    // Bind deferred rendering mode. This can be configured from the editor,
    // and shader sets the fragment color according to this mode:
    program->BindUniformInts("mode", 1, &deferred_mode);

    RenderDeferredQuad();

    Program::Deactivate();

    // Blit g_buffer depth buffer to frame_buffer to be used for forward 
    // rendering pass:
    g_buffer_deneme.BlitDepth(frame_buffer, fb_width, fb_height);

    // Enable blending for the next passes:
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (draw_skybox)
    {
        scene->GetSkybox()->Draw(camera);
    }

    // Draw debug draw stuff:
    ModuleDebugDraw::Draw(camera->GetViewMatrix(), 
        camera->GetProjectionMatrix(), fb_height, fb_width);

    // If forward pass is disabled on the settings, return:
    if (!render_forward_pass)
    {
        return;
    }

    // Forward rendering pass for transparent game objects:
    program = App->program->GetMainProgram();

    program->Activate();

    // Get the targets that has transparent materials. These targets will be 
    // rendered with regular forward rendering pass:
    std::vector<RenderTarget>& transparent_targets = render_list.GetTransparentTargets();

    for (RenderTarget target : transparent_targets)
    {
        target.mesh_renderer->Draw(camera, program);
    }

    Program::Deactivate();

    /*if (outline_selection && outline_target)
    {
        glStencilFunc(GL_NOTEQUAL, 1, 0XFF);
        glStencilMask(0X00);
        glDisable(GL_DEPTH_TEST);

        Program* outline_program = App->program->GetStencilProgram();
        outline_program->Activate();
        outline_target->game_object->DrawStencil(camera, outline_program);
        Program::Deactivate();

        glStencilMask(0XFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);
    }*/
}

UpdateStatus Hachiko::ModuleRender::PostUpdate(const float delta)
{
    SDL_GL_SwapWindow(App->window->GetWindow());
    AddFrame(delta);

    return UpdateStatus::UPDATE_CONTINUE;
}

void GLOptionCheck(GLenum option, bool enable)
{
    if (enable)
    {
        glEnable(option);
    }
    else
    {
        glDisable(option);
    }
}

void Hachiko::ModuleRender::OptionsMenu()
{
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Draw Options");
    ImGui::Checkbox("Debug Draw", &App->debug_draw->debug_draw);
    ImGui::Checkbox("Quadtree", &App->debug_draw->draw_quadtree);
    ImGui::Checkbox("Skybox", &draw_skybox);
    ImGui::Checkbox("Navmesh", &draw_navmesh);
    
    DeferredOptions();

    if (!draw_skybox)
    {
        ImGuiUtils::CompactColorPicker("Background Color", App->editor->scene_background.ptr());
    }
}

void Hachiko::ModuleRender::DeferredOptions() 
{
    ImGui::NewLine();

    ImGui::Text("Deferred Rendering Options");
    ImGui::Separator();

    ImGui::PushID("Deferred Options");

    if (ImGui::RadioButton("Lighting Pass", deferred_mode == 0))
    {
        deferred_mode = 0;
    }

    if (ImGui::RadioButton("Diffuse", deferred_mode == 1))
    {
        deferred_mode = 1;
    }

    if (ImGui::RadioButton("Specular", deferred_mode == 2))
    {
        deferred_mode = 2;
    }
    
    if (ImGui::RadioButton("Smoothness", deferred_mode == 3))
    {
        deferred_mode = 3;
    }
    
    if (ImGui::RadioButton("Normal", deferred_mode == 4))
    {
        deferred_mode = 4;
    }

    if (ImGui::RadioButton("Position", deferred_mode == 5))
    {
        deferred_mode = 5;
    }

    if (ImGui::RadioButton("Emissive", deferred_mode == 6))
    {
        deferred_mode = 6;
    }

    ImGui::Checkbox("Forward Rendering Pass", &render_forward_pass);

    ImGui::NewLine();

    ImGui::PopID();
}

void Hachiko::ModuleRender::PerformanceMenu()
{
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vram_free);
    const float vram_free_mb = vram_free / 1024.0f;
    const float vram_usage_mb = gpu.vram_budget_mb - vram_free_mb;
    ImGui::Text("VRAM Budget: %.1f Mb", gpu.vram_budget_mb);
    ImGui::Text("Vram Usage:  %.1f Mb", vram_usage_mb);
    ImGui::Text("Vram Avaliable:  %.1f Mb", vram_free_mb);
    ImGui::Separator();
    FpsGraph();
}

void Hachiko::ModuleRender::FpsGraph() const
{
    ImGui::Text("Fps: %.1f", current_fps);

    char title[25];
    sprintf_s(title, 25, "Framerate %.1f", current_fps);
    ImGui::PlotHistogram("##framerate", &fps_log[0], static_cast<int>(fps_log.size()), 0, title, 0.0f, 1000.f, ImVec2(310, 100));
    sprintf_s(title, 25, "Milliseconds %0.1f", current_ms);
    ImGui::PlotHistogram("##milliseconds", &ms_log[0], static_cast<int>(ms_log.size()), 0, title, 0.0f, 20.0f, ImVec2(310, 100));
}

void Hachiko::ModuleRender::AddFrame(const float delta)
{
    static constexpr float update_frequency_seconds = 0.5f;
    static int filled_bins = 0;
    static int frames = 0;
    static float time = 0;

    ++frames;
    time += delta;

    if (time >= update_frequency_seconds)
    {
        if (filled_bins == n_bins)
        {
            for (int i = 0; i < n_bins - 1; ++i)
            {
                fps_log[i] = fps_log[i + 1];
                ms_log[i] = ms_log[i + 1];
            }
        }
        else
        {
            ++filled_bins;
        }
        fps_log[filled_bins - 1] = static_cast<float>(frames) / time;
        current_fps = fps_log[filled_bins - 1];
        ms_log[filled_bins - 1] = time * 1000.0f / static_cast<float>(frames);
        current_ms = ms_log[filled_bins - 1];
        time = 0;
        frames = 0;
    }
}

void Hachiko::ModuleRender::RetrieveLibVersions()
{
    HE_LOG("GPU Vendor: %s", glGetString(GL_VENDOR));
    HE_LOG("Renderer: %s", glGetString(GL_RENDERER));
    HE_LOG("Using Glew %s", glewGetString(GLEW_VERSION));
    HE_LOG("OpenGL version supported %s", glGetString(GL_VERSION));
    HE_LOG("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Hachiko::ModuleRender::RetrieveGpuInfo()
{
    gpu.name = (unsigned char*)glGetString(GL_RENDERER);
    gpu.brand = (unsigned char*)glGetString(GL_VENDOR);

    int vram_budget;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &vram_budget);
    gpu.vram_budget_mb = static_cast<float>(vram_budget) / 1024.0f;
}

void Hachiko::ModuleRender::GenerateDeferredQuad() 
{
    constexpr const float vertices[] = {
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top right
        1.0f,  -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f,  0.0f, 0.0f, 1.0f // top left
    };
    constexpr unsigned int indices[] = {2, 1, 0, 0, 3, 2};

    glGenVertexArrays(1, &deferred_quad_vao);
    glGenBuffers(1, &deferred_quad_vbo);
    glGenBuffers(1, &deferred_quad_ebo);

    glBindVertexArray(deferred_quad_vao);

    glBindBuffer(GL_ARRAY_BUFFER, deferred_quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deferred_quad_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertices:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinates:
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Hachiko::ModuleRender::RenderDeferredQuad() const 
{
    glBindVertexArray(deferred_quad_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Hachiko::ModuleRender::FreeDeferredQuad() 
{
    glBindVertexArray(deferred_quad_vao);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &deferred_quad_ebo);
    glDeleteBuffers(1, &deferred_quad_vbo);
    glDeleteVertexArrays(1, &deferred_quad_vao);
    glBindVertexArray(0);
}

bool Hachiko::ModuleRender::CleanUp()
{
    FreeDeferredQuad();

    glDeleteTextures(1, &fb_texture);
    glDeleteBuffers(1, &depth_stencil_buffer);
    glDeleteBuffers(1, &frame_buffer);

    SDL_GL_DeleteContext(context);

    return true;
}