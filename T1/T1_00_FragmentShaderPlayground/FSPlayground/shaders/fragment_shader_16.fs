#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  vec2 uv = gl_FragCoord.xy / u_window_size;

  float aspect_ratio = u_window_size.x / u_window_size.y;
  uv.x *= aspect_ratio;

  vec2 center_pacman = vec2(0.5 * aspect_ratio, 0.5);
  float dist = distance(uv, center_pacman);
  float radius = 0.15;

  vec2 offset = uv - center_pacman;
  float angle = atan(offset.y, offset.x);

  vec3 background_color = vec3(0.9, 0.9, 0.8);
  vec3 color = background_color;

  if(dist < radius){
    if(angle < -0.5 || angle > 0.5){
      color = vec3(1.0,1.0,0.0);
    }
  }

  vec2 center_eye = center_pacman + vec2(0.05, 0.08);
  float dist_eye = distance(uv, center_eye);
  float eye_radius = 0.015;
  if(dist_eye < eye_radius){
    color = background_color;
  }

  fragColor = vec4(color, 1.0);

}
