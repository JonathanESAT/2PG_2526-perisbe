/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022.
 * 
 * PR04_00_GPUManager_Template.cc
 * 
 */

#include <stdio.h>
#include <math.h>
#include "ESAT/window.h"
#include "ESAT/input.h"
#include "ESAT/draw.h"
#include "ESAT/time.h"

#include "EDK/edk_camera.h"
#include "EDK/edk_geometry.h"
#include "EDK/edk_drawable.h"
#include "EDK/edk_material_diffuse_texture.h"
#include "EDK/edk_texture.h"
#include "EDK/edk_render_target.h"
#include "EDK/edk_material_postprocess.h"
#include "EDK/dev/edk_gpu_manager.h"
#include "dev/custom_gpu_manager.h"
//#include "dev/custom_gpu_camera.h"

#include "ESAT_extra/imgui.h"
#include "EDK/dev/edk_opengl.h"


//Unnamed struct and it's unique instance:
struct {
  //EDK::ref_ptr<EDK::dev::CustomGPUCamera> camera;
  EDK::ref_ptr<EDK::Camera> camera;
  EDK::ref_ptr<EDK::Node> root;
  EDK::ref_ptr<EDK::RenderTarget> render_target;
  EDK::ref_ptr<EDK::MatPostprocess> postprocess_material;
  EDK::ref_ptr<EDK::MatPostprocess::Blur> blur_v;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;


void InitScene() {
  //Initializing the font:
  esat::DrawSetTextFont("./test/Font.ttf");
  esat::DrawSetTextSize(18);
  esat::DrawSetFillColor(255, 255, 255, 128);

  EDK::dev::GPUManager::CheckGLError("Initializing the scene...");
  
  //Creating a cube:
  EDK::ref_ptr<EDK::Geometry> quad_geo;
  EDK::CreateQuad(&quad_geo, 35.0f, 28.0f, true, true);

  //Loading texture:
  EDK::ref_ptr<EDK::Texture> texture;
  EDK::Texture::Load("./test/T_EDK_Logo.png", &texture);
  if (!texture) {
    printf("Can't load T_EDK_Logo.png\n");
    exit(-2);
  }

  //Initializing the material and its settings:
  EDK::ref_ptr<EDK::MatDiffuseTexture> mat_diff_text;
  mat_diff_text.alloc();
  EDK::ref_ptr<EDK::MatDiffuseTexture::Settings> mat_diff_text_settings;
  mat_diff_text_settings.alloc();
  mat_diff_text_settings->set_lightColor(1.0f, 1.0f, 1.0f, 1.0f);
  mat_diff_text_settings->set_texture(texture.get());

  //Allocating root node:
  EDK::Node* root = GameState.root.alloc();

  //Allocating and initializing the render target and its material:
  GameState.render_target.alloc()->init((float) kWindowWidth,
                                        (float) kWindowHeight, 1);
  GameState.postprocess_material.alloc();

  //Allocating and initializing the vertical blur postprocess:
  GameState.blur_v.alloc();
  GameState.blur_v->set_texture(GameState.render_target->color_texture(0));
  GameState.blur_v->set_direction(EDK::MatPostprocess::Blur::kVertical);

  //Creates the drawables (Geometry + Material + Settings):
  EDK::ref_ptr<EDK::Drawable> drawable;
  for (int i = -10; i < 10; i++) {
    for (int j = -10; j < 10; j++) {
      drawable.alloc();
      drawable->set_geometry(quad_geo.get());
      drawable->set_material(mat_diff_text.get());
      drawable->set_material_settings(mat_diff_text_settings.get());
      drawable->set_position(i * 70.0f, 0.0f, j * 70.0f);
      drawable->set_HPR(360.0f * rand() / RAND_MAX, 
                        360.0f * rand() / RAND_MAX, 
                        360.0f * rand() / RAND_MAX);
      root->addChild(drawable.get());
    }
  }

  //Allocating and initializing the camera:
  GameState.camera.alloc();
  float pos[] = { 120.0f, 140.0f, 120.0f };
  float view[] = { -120.0f, -140.0f, -120.0f };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
  float ar = (float) kWindowWidth / (float) kWindowHeight;
  GameState.camera->setupPerspective(70.0f, ar, 1.0f, 1500.0f);
  EDK::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn() {
  //Updates the root node:
  GameState.root->set_rotation_y(5.0f * esat::Time() * 0.001f);

  //Orbital camera:
  double mx = esat::MousePositionX();
  double my = esat::MousePositionY();
  double p = sin(-my / 200.0f) * 220.0f;
  float pos[] = { (float)(p * cos(mx * 0.01f)),
                  (float)cos(-my / 200) * 220.0f,
                  (float)(p * sin(mx * 0.01f)) };
  float view[] = { -pos[0], -pos[1], -pos[2] };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_direction(view);
  GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
}

void RenderFn() {
  EDK::dev::GPUManager::Instance()->enableCullFaces(EDK::dev::GPUManager::FaceType::kFace_Back);

  //For every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());

  //Render the scene to a render target:
  GameState.render_target->begin();
  GameState.camera->doRender();
  GameState.render_target->end();

  //Rendering the scene:
  GameState.postprocess_material->drawFullScreenQuad(GameState.blur_v.get());
}

void ImGuiFn(double dt) {
  ImGui::Begin("FPS Window");
  ImGui::Text("FPS: %0.1f", 1000.0 / dt);
  ImGui::Text("Delta time: %0.3f ms", dt);
  ImGui::End();
  ImGui::Render();
}

int esat::main(int argc, char** argv) {
  //TODO programmer use your custom GPU Manager:
  EDK::dev::CustomGPUManager gpu_implementation;
  EDK::dev::GPUManager::ReplaceGPUManagerImplementation(&gpu_implementation);

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
