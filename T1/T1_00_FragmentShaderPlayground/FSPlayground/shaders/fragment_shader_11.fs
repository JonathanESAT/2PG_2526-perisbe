#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  float num_stripes = 6.0;
  float frequency = num_stripes * 6.28;
  vec2 uv = (gl_FragCoord.xy / u_window_size);

  float wave_xy= sin((uv.x + uv.y) * frequency / 2) * 0.5 + 0.5;
  float stripes_xy = smoothstep(0.6, 0.85, wave_xy);



  fragColor = vec4(stripes_xy, stripes_xy,0.0,1.0);

}
