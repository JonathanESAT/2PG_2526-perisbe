#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec3 v_normal;


void main() {
  float s = step(0.5, v_normal.z);
  fragColor = vec4(s, 0.0, 0.0, 1.0);
}
