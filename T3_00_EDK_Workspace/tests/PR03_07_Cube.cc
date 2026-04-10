/*
 *
 * Ivan Sancho as Unreal Authorized Instructor, 2022-23
 * Graphics Programming
 *
 * PR03_05_CustomMaterial.cc
 *
 */
#include <stdio.h>
#include <math.h>
#include "ESAT/window.h"
#include "ESAT/input.h"
#include "ESAT/draw.h"
#include "ESAT/time.h"
#include "EDK/edk_geometry.h"
#include "EDK/edk_camera.h"
#include "EDK/edk_drawable.h"
#include "EDK/edk_material_diffuse_texture.h"
#include "EDK/edk_material_diffuse.h"
#include "include/material_custom.h"
#include "EDK/edk_texture.h"
#include "EDK/dev/edk_gpu_manager.h"
#include "ESAT_extra/imgui.h"
#include "EDK/dev/edk_opengl.h"
#include "geometry_custom_cube.h"

struct {
    EDK::ref_ptr<EDK::Camera> camera;
    EDK::ref_ptr<EDK::Node> root;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;

void InitScene() {
    EDK::Node* root = GameState.root.alloc();

    char* paths[] = { "./test/lobatin.jpg" , "./test/T_Rainbow.png" };
    float blue[] = { 0.0f, 1.0f, 0.0f, 1.0f };

    EDK::ref_ptr<EDK::Texture> texture1;
    EDK::Texture::Load(paths[0], &texture1);
    EDK::ref_ptr<EDK::Texture> texture2;
    EDK::Texture::Load(paths[1], &texture2);

    EDK::ref_ptr<EDK::MaterialCustom> cube_mat_lobatin8v;
    cube_mat_lobatin8v.alloc();
    cube_mat_lobatin8v->init("./test/material_custom.vs", "./test/material_custom_b.fs");
    EDK::ref_ptr<EDK::MaterialCustom::MaterialCustomSettings> settings8v;
    settings8v.alloc();
    settings8v->set_color(blue);

    EDK::ref_ptr<EDK::MaterialCustom> cube_mat_lobatin24v;
    cube_mat_lobatin24v.alloc();
    cube_mat_lobatin24v->init("./test/material_custom.vs", "./test/material_custom_b.fs");
    EDK::ref_ptr<EDK::MaterialCustom::MaterialCustomSettings> settings24v;
    settings24v.alloc();
    settings24v->set_color(blue);



    float pos_cube[4][3] = { { 2.0f, 2.0f, 0.0f }, { -2.0f, 2.0f, 0.0f },
                             { 2.0f, -1.0f, 0.0f }, { -2.0f, -1.0f, 0.0f } };

    EDK::ref_ptr<EDK::MatDiffuse> mat;
    mat.alloc();
    EDK::ref_ptr<EDK::MatDiffuse::Settings> mat_set;
    mat_set.alloc();


    float color[4] = { 0.0f,1.0f,0.5f,1.0f };
    mat_set->set_color(color);

    //24v cubes
    EDK::ref_ptr <EDK::CubeCustom> cube;
    cube.alloc();
    cube->init24v();

    EDK::ref_ptr<EDK::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(cube.get());
    drawable->set_material(mat.get());
    drawable->set_material_settings(mat_set.get());
    drawable->set_position(pos_cube[0]);
    root->addChild(drawable.get());

    EDK::ref_ptr <EDK::CubeCustom> mat_cube;
    mat_cube.alloc();
    mat_cube->init24v();

    EDK::ref_ptr<EDK::Drawable> mat_drawable;
    mat_drawable.alloc();
    mat_drawable->set_geometry(mat_cube.get());
    mat_drawable->set_material(cube_mat_lobatin24v.get());
    mat_drawable->set_material_settings(settings24v.get());
    mat_drawable->set_position(pos_cube[2]);
    root->addChild(mat_drawable.get());

    //8v cubes
    EDK::ref_ptr <EDK::CubeCustom> bad_cube;
    bad_cube.alloc();
    bad_cube->init8v();

    EDK::ref_ptr<EDK::Drawable> bad_drawable;
    bad_drawable.alloc();
    bad_drawable->set_geometry(bad_cube.get());
    bad_drawable->set_material(mat.get());
    bad_drawable->set_material_settings(mat_set.get());
    bad_drawable->set_position(pos_cube[1]);
    root->addChild(bad_drawable.get());

    EDK::ref_ptr <EDK::CubeCustom> bad_mat_cube;
    bad_mat_cube.alloc();
    bad_mat_cube->init8v();

    EDK::ref_ptr<EDK::Drawable> bad_mat_drawable;
    bad_mat_drawable.alloc();
    bad_mat_drawable->set_geometry(bad_mat_cube.get());
    bad_mat_drawable->set_material(cube_mat_lobatin8v.get());
    bad_mat_drawable->set_material_settings(settings8v.get());
    bad_mat_drawable->set_position(pos_cube[3]);
    root->addChild(bad_mat_drawable.get());

    // Camera
    GameState.camera.alloc();
    float pos[] = { 0.0f, 3.0f, 4.0f };
    float view[] = { 0.0f, 0.0f, 0.0f };
    GameState.camera->set_position(pos);
    GameState.camera->set_view_target(view);
    GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
    EDK::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn() {
    GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
    GameState.root->child(0)->set_rotation_y(-esat::Time() * 0.1);
    GameState.root->child(1)->set_rotation_y(esat::Time() * 0.1);
    GameState.root->child(2)->set_rotation_y(-esat::Time() * 0.1);
    GameState.root->child(3)->set_rotation_y(esat::Time() * 0.1);
}

void RenderFn() {
    GameState.camera->doCull(GameState.root.get());
    EDK::dev::GPUManager::CheckGLError("begin Render-->");
    GameState.camera->doRender();
    EDK::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double dt) {
    ImGui::Begin("FPS Window");
    ImGui::Text("FPS: %0.1f", 1000.0 / dt);
    ImGui::Text("Delta time: %0.3f ms", dt);
    ImGui::End();
    ImGui::Render();
}

int esat::main(int argc, char** argv) {
    esat::WindowInit(kWindowWidth, kWindowHeight);
    InitScene();
    double dt = 0.0;
    double last_time = esat::Time();
    while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
        esat::WindowIsOpened()) {
        UpdateFn();
        RenderFn();
        dt = esat::Time() - last_time;
        last_time = esat::Time();
        ImGuiFn(dt);
        esat::WindowFrame();
    }
    return 0;
}