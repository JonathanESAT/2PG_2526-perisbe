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
#include "EDK/edk_texture.h"
#include "EDK/dev/edk_gpu_manager.h"

#include "ESAT_extra/imgui.h"
#include "EDK/dev/edk_opengl.h"


//Unnamed struct and it's unique instance:
struct {
  EDK::ref_ptr<EDK::Camera> camera;
  EDK::ref_ptr<EDK::Node> root;
  EDK::ref_ptr<EDK::Node> pivot;
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;


void InitScene() {
  //Allocating root node:
  EDK::Node* root = GameState.root.alloc();

  char* paths[] = { "./test/T_Chopper.jpg",
                    "./test/T_EDK_Logo.png",
                    "./test/SM_Suzanne.obj",
                    "./test/T_Rainbow.png"};

  float pos_cubes[3][3] = { { 2.0f, 0.0f, 0.0f},
						                { -2.0f, 0.0f,0.0f},
                            { 0.0f, 2.0f, 0.0f} };

  // Pivot at monkey position: cubes will orbit around it
  EDK::Node* pivot = GameState.pivot.alloc();
  pivot->set_position(pos_cubes[2]);
  root->addChild(pivot);

  //Geometry:
  EDK::ref_ptr<EDK::Geometry> cube_geo;
  EDK::CreateCube(&cube_geo);



    //Material, settings:

  EDK::ref_ptr<EDK::MatDiffuseTexture> cube_mat;
  cube_mat.alloc();
  float color[4] = { 1.0,1.0,1.0,1.0 };

  for (int i = 0; i < 2; i++) {

      EDK::ref_ptr<EDK::Texture> cube_texture;
      EDK::Texture::Load(paths[i], &cube_texture); //alloc inside

      EDK::ref_ptr<EDK::MatDiffuseTexture::Settings> cube_mat_set;
      cube_mat_set.alloc();

      cube_mat_set->set_color(color);
      cube_mat_set->set_texture(cube_texture.get());

      //Drawable:
      EDK::ref_ptr<EDK::Drawable> cube_drawable;
      cube_drawable.alloc();

      cube_drawable->set_geometry(cube_geo.get());
      cube_drawable->set_material(cube_mat.get());
      cube_drawable->set_material_settings(cube_mat_set.get());
      cube_drawable->set_position(pos_cubes[i]);

      pivot->addChild(cube_drawable.get());
  }

  //OBJ:
  EDK::scoped_array<EDK::ref_ptr<EDK::Geometry>> obj_geos;
  EDK::scoped_array<char> error_log;
  EDK::LoadObj(paths[2], &obj_geos, &error_log);

  EDK::ref_ptr<EDK::Texture> obj_texture;
  EDK::Texture::Load(paths[3], &obj_texture);

  EDK::ref_ptr<EDK::MatDiffuseTexture::Settings> obj_mat_set;
  obj_mat_set.alloc();
  obj_mat_set->set_color(color);
  obj_mat_set->set_texture(obj_texture.get());

  EDK::ref_ptr<EDK::Drawable> obj_drawable;
  obj_drawable.alloc();
  obj_drawable->set_geometry(obj_geos[0].get());
  obj_drawable->set_material(cube_mat.get());
  obj_drawable->set_material_settings(obj_mat_set.get());
  obj_drawable->set_position(pos_cubes[2]);
  root->addChild(obj_drawable.get());


  //Allocating and initializing the camera:
  GameState.camera.alloc();
  float pos[] = { 0.0f, 4.0f, 6.0f };
  float target[] = { 0.0f, 0.0f, 0.0f };
  GameState.camera->set_position(pos);
  GameState.camera->set_view_target(target);
  float ar = (float) kWindowWidth / (float) kWindowHeight;
  GameState.camera->setupPerspective(60.0f, ar, 1.0f, 1500.0f);
  EDK::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn(double delta_time) {
  GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
  static float rotation = 0.0f;
  rotation += (float)(delta_time * 0.09f);
  GameState.root->child(1)->set_rotation_y(rotation);  // mono gira sobre si mismo
  GameState.pivot->set_rotation_y(rotation);            // pivot orbita los cubos alrededor del mono
}

void RenderFn() {
  //For every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());

  //Rendering the scene:
  EDK::dev::GPUManager::CheckGLError("begin Render-->");
  GameState.camera->doRender();
  EDK::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double delta_time) {
  ImGui::Begin("FPS Window");
  ImGui::Text("FPS: %0.1f", 1000.0 / delta_time);
  ImGui::Text("Delta time: %0.3f ms", delta_time);
  ImGui::End();
  ImGui::Render();
}

int esat::main(int argc, char** argv) {
  esat::WindowInit(kWindowWidth, kWindowHeight);
  InitScene();
  double delta_time = 0.0;
  double last_time = esat::Time();
  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    delta_time = esat::Time() - last_time;
    last_time = esat::Time();
    UpdateFn(delta_time);
    RenderFn();
    ImGuiFn(delta_time);
    esat::WindowFrame();
  }
  return 0;
}
