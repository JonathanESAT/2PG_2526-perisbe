#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec3 v_normal;


void main() {

  vec3 color = (v_normal + 1.0) * 0.5;
  fragColor = (vec4(color,1.0));
}
