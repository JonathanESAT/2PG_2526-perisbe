#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec3 v_normal;


void main() {

  vec3 light_direction = vec3(0.0,0.0,1.0);

  float dot_product = dot(v_normal, light_direction);

  fragColor = vec4(1.0,0.0,0.0,1.0) * max(0.0, dot_product);
}
