#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  vec2 uv = gl_FragCoord.xy / u_window_size;

  float smooth_x = smoothstep(0.49,0.51,uv.x);
  float smooth_y = smoothstep(0.49,0.51,uv.y);
  fragColor = vec4(smooth_x, smooth_y,0.0,0.0);
 
  
}
