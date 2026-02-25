/*
 *
 * Ivan Sancho as Unreal Authorized Instructor, 2022-23
 * Graphics Programming
 *
 * PR03_00_Template.cc
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
#include "material_custom.h"
#include "EDK/edk_texture.h"
#include "EDK/dev/edk_gpu_manager.h"

#include "ESAT_extra/imgui.h"
#include "EDK/dev/edk_opengl.h"


 //Unnamed struct and it's unique instance:
struct {
    EDK::ref_ptr<EDK::Camera> camera;
    EDK::ref_ptr<EDK::Node> root;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;


void InitScene() {
    //Allocating root node:
    EDK::Node* root = GameState.root.alloc();

    char* paths[] = { "./test/T_Chopper.jpg" , "./test/T_Rainbow.png" };

    //Geometry
    EDK::ref_ptr<EDK::Geometry> cube_geo;
    EDK::CreateCube(&cube_geo);
    EDK::ref_ptr<EDK::MaterialCustom> cube_mat_A;
    cube_mat_A.alloc();
    EDK::ref_ptr<EDK::MaterialCustom> cube_mat_B;
    cube_mat_B.alloc();
    float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    EDK::ref_ptr<EDK::Node> cube_base;
    cube_base.alloc();
    cube_mat_A->init("./test/material_custom.vs", "./test/material_custom_A.fs");
    cube_mat_B->init("./test/material_custom.vs", "./test/material_custom_B.fs");
    root->addChild(cube_base.get());
    float pos_cube[2][3] = { { 2.0f, 0.0f, 0.0f }, { -2.0f, 0.0f, 0.0f } };
    for (int i = 0; i < 2; i++)
    {
        //Material settings:
        EDK::ref_ptr<EDK::MaterialCustom::MaterialCustomSettings> cube_mat_settings;
        cube_mat_settings.alloc();
        cube_mat_settings->set_color(color);
        //Drawable
        EDK::ref_ptr<EDK::Drawable> cube_drawable;
        cube_drawable.alloc();
        cube_drawable->set_geometry(cube_geo.get());
        cube_drawable->set_material(i == 0 ? cube_mat_A.get() : cube_mat_B.get());
        cube_drawable->set_material_settings(cube_mat_settings.get());
        cube_drawable->set_position(pos_cube[i]);
        cube_base->addChild(cube_drawable.get());
    }

    //****************MONKE**********************************************

    float monke_angle = (float)esat::Time() * 0.000005;
    float monke_pos[3] = { 0.0f, monke_angle, 0.0f };


    EDK::ref_ptr<EDK::Node> monke_node;
    monke_node.alloc();

    EDK::ref_ptr<EDK::Texture> monke_texture;
    EDK::Texture::Load("./test/biden.png", &monke_texture);

    EDK::ref_ptr<EDK::MaterialCustom::MaterialCustomSettings> monke_mat_settings;
    monke_mat_settings.alloc();
    monke_mat_settings->set_color(color);

    EDK::scoped_array<EDK::ref_ptr<EDK::Geometry>> monke_geo;
    EDK::scoped_array<char> error_monke;
    EDK::LoadObj("./test/biden.obj", &monke_geo, &error_monke);
    int num_geos = monke_geo.size();
    for (int i = 0; i < num_geos; i++)
    {
        EDK::ref_ptr<EDK::Drawable> monke_draw;
        monke_draw.alloc();
        monke_draw->scale();
        monke_draw->set_geometry(monke_geo[i].get());
        monke_draw->set_material(i == 0 ? cube_mat_A.get() : cube_mat_B.get());
        monke_draw->set_material_settings(monke_mat_settings.get());
        monke_node->addChild(monke_draw.get());
    }
    root->addChild(monke_node.get());

    monke_node->set_position(monke_pos);
    //*******************************************************************
    //ICE CREAM

    //Allocating and initializing the camera:
    GameState.camera.alloc();
    float pos[] = { 0.0f, 4.0f, 6.0f };
    float target[] = { 0.0f, 0.0f, 0.0f };
    GameState.camera->set_position(pos);
    GameState.camera->set_view_target(target);
    float ar = (float)kWindowWidth / (float)kWindowHeight;
    GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
    EDK::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn() {
    float biden_scale[3] = { 25.0f, 25.0f, 25.0f };
    GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
    GameState.root->child(0)->set_rotation_y(-esat::Time() * 0.1);//cubes root
    GameState.root->child(1)->set_rotation_y(esat::Time() * 0.01);//monke
    GameState.root->child(1)->set_scale(biden_scale);//monke
}

void RenderFn() {
    //For every frame... determine what's visible:
    GameState.camera->doCull(GameState.root.get());

    //Rendering the scene:
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
