#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec3 normal;
in vec2 uv;

void main() {
  fragColor = vec4(normal, 1.0);
}
