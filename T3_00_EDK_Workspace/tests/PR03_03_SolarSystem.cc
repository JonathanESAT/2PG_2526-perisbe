/*
 *
 * Ivan Sancho as Unreal Authorized Instructor, 2022-23
 * Graphics Programming
 *
 * PR03_03_SolarSystem.cc
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


const int kNumPlanets = 4;

struct PlanetData {
  EDK::ref_ptr<EDK::Node>     orbit_pivot;
  EDK::ref_ptr<EDK::Drawable> drawable;
  float orbit_speed;
  float self_speed;
};

struct {
  EDK::ref_ptr<EDK::Camera>   camera;
  EDK::ref_ptr<EDK::Node>     root;
  EDK::ref_ptr<EDK::Drawable> sun;
  PlanetData planets[4];
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

  EDK::ref_ptr<EDK::Geometry> cube_geo;
  EDK::CreateCube(&cube_geo, 1.0f, true, true);

  EDK::ref_ptr<EDK::MatDiffuseTexture> mat;
  mat.alloc();

  //Sol:
  {
    EDK::ref_ptr<EDK::MatDiffuseTexture::Settings> s;
    s.alloc();
    float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    s->set_color(white);
    s->set_texture(texture.get());

    GameState.sun.alloc();
    GameState.sun->set_geometry(cube_geo.get());
    GameState.sun->set_material(mat.get());
    GameState.sun->set_material_settings(s.get());
    GameState.sun->set_scale(20.0f, 20.0f, 20.0f);
    root->addChild(GameState.sun.get());
  }

  //Planetas: orbit_radius, scale, orbit_speed, self_speed
  const float kCfg[4][4] = {
    {  40.0f, 3.5f, 20.0f, 60.0f },
    {  65.0f, 5.0f, 12.0f, 45.0f },
    {  95.0f, 6.5f,  7.0f, 30.0f },
    { 130.0f, 5.5f,  4.0f, 20.0f },
  };

  for (int i = 0; i < kNumPlanets; ++i) {
    //Pivot: al rotarlo, el planeta orbita el sol
    EDK::Node* pivot = GameState.planets[i].orbit_pivot.alloc();
    root->addChild(pivot);

    EDK::ref_ptr<EDK::MatDiffuseTexture::Settings> s;
    s.alloc();
    float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    s->set_color(white);
    s->set_texture(texture.get());

    EDK::Drawable* planet = GameState.planets[i].drawable.alloc();
    planet->set_geometry(cube_geo.get());
    planet->set_material(mat.get());
    planet->set_material_settings(s.get());
    planet->set_position(kCfg[i][0], 0.0f, 0.0f);
    planet->set_scale(kCfg[i][1], kCfg[i][1], kCfg[i][1]);
    pivot->addChild(planet);

    GameState.planets[i].orbit_speed = kCfg[i][2];
    GameState.planets[i].self_speed  = kCfg[i][3];
  }

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

  for (int i = 0; i < kNumPlanets; ++i) {
    GameState.planets[i].orbit_pivot->set_rotation_y(t * GameState.planets[i].orbit_speed);
    GameState.planets[i].drawable->set_rotation_y(t * GameState.planets[i].self_speed);
  }
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
