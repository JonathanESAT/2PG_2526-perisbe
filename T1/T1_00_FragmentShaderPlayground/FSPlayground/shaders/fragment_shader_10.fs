#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  float num_stripes = 10.0;
  float frequency = 10.0 * 6.28;
  vec2 uv = (gl_FragCoord.xy / u_window_size);

  float wave = sin(uv.x * frequency) * 0.5 + 0.5;
  float stripes = smoothstep(0.6, 0.85, wave);

  fragColor = vec4(stripes, 0.0,0.0,1.0);

}
