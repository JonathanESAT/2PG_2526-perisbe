#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  vec2 uv = gl_FragCoord.xy / u_window_size;

  vec2 centro = vec2(0.5,0.6);

  float aspect_ratio = u_window_size.x / u_window_size.y;
  uv.x *= aspect_ratio;
  centro.x *= aspect_ratio;
  
  float dist = distance(uv, centro);

  float ring_inner = 0.11;
  float ring_outer = 0.23;

  vec3 background_color = vec3(0.9, 0.9, 0.8);
  vec3 cyan_color = vec3(0.5, 0.85, 0.85);
  vec3 orange_color = vec3(0.95, 0.55, 0.30);

  vec3 final_color = background_color;

  float blend_factor = (dist - ring_inner) / (ring_outer - ring_inner);
  vec3 ring_color = mix(cyan_color, orange_color, blend_factor);

  float in_ring = step(ring_inner, dist) * (1.0 - step(ring_outer,dist));
  final_color = mix(background_color, ring_color, in_ring);

  fragColor = vec4(final_color, 1.0);


}
