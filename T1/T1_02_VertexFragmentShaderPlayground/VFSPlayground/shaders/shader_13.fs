#version 330

uniform sampler2D u_texture;
out vec4 fragColor;


in vec2 uv;

void main() {
  vec3 cube_color = vec3(0.878, 0.894, 0.8);
  vec3 outer_color = vec3(0.2, 0.6, 0.8);
  vec3 inner_color = vec3(0.8, 0.6, 0.2);

  vec2 center = vec2(0.5,0.5);
  vec2 dir = uv - center;  //[-0.5,0.5]
  dir *= 2.0; //[-1.0, 1.0]
  float dir_length = length(dir);

  //Outer radius:
  float outer_radius = 0.8;
  float os = step(dir_length, outer_radius);

  //Inner radius:
  float inner_radius = 0.6;
  float is = step(inner_radius, dir_length);

  float alpha = (dir_length - inner_radius) / (outer_radius - inner_radius);
  alpha = clamp(alpha, 0.0, 1.0);
  vec3 color = mix(inner_color, outer_color, alpha);
  color = mix(cube_color, color, is);
  color = mix(cube_color, color, os);
  fragColor = vec4(color, 1.0);
}
