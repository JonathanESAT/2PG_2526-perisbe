/*
 *
 * Ivan Sancho as Unreal Authorized Instructor, 2022-23
 * Graphics Programming
 *
 * PR03_02_FirstScene.cc
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
#include "EDK/edk_texture.h"
#include "EDK/dev/edk_gpu_manager.h"

#include "ESAT_extra/imgui.h"
#include "EDK/dev/edk_opengl.h"


struct {
  EDK::ref_ptr<EDK::Camera>   camera;
  EDK::ref_ptr<EDK::Node>     root;
  EDK::ref_ptr<EDK::Drawable> sun;
} GameState;

const int kWindowWidth  = 1024;
const int kWindowHeight = 768;


void InitScene() {
  EDK::Node* root = GameState.root.alloc();

  EDK::ref_ptr<EDK::Texture> texture;
  EDK::Texture::Load("./test/T_EDK_Logo.png", &texture);
  if (!texture) {
    printf("Can't load T_EDK_Logo.png\n");
    exit(-2);
  }

  EDK::ref_ptr<EDK::MatDiffuseTexture> mat;
  mat.alloc();

  EDK::ref_ptr<EDK::MatDiffuseTexture::Settings> mat_set;
  mat_set.alloc();
  float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  mat_set->set_color(white);
  mat_set->set_texture(texture.get());

  EDK::ref_ptr<EDK::Geometry> cube_geo;
  EDK::CreateCube(&cube_geo, 1.0f, true, true);

  //Sol:
  GameState.sun.alloc();
  GameState.sun->set_geometry(cube_geo.get());
  GameState.sun->set_material(mat.get());
  GameState.sun->set_material_settings(mat_set.get());
  GameState.sun->set_scale(20.0f, 20.0f, 20.0f);
  root->addChild(GameState.sun.get());

  //Camara:
  GameState.camera.alloc();
  float pos[]  = { 120.0f, 140.0f, 120.0f };
  float view[] = { -120.0f, -140.0f, -120.0f };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
  GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
  EDK::dev::GPUManager::CheckGLError("Prepare END");
}


void UpdateFn() {
  GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);

  float t = (float)(esat::Time() * 0.001f);
  GameState.sun->set_rotation_y(t * 30.0f);
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
