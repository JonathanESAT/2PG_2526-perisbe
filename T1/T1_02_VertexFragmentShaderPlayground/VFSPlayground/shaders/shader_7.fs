#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec3 vertexColor;


void main() {
  fragColor = vec4(vertexColor, 1.0);
}
