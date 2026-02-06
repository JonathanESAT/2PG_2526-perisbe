#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {

  float aspect_ratio = u_window_size.x / u_window_size.y;
  float num_stripes = 20;
  float frequency = num_stripes * 6.28;
  vec2 uv = (gl_FragCoord.xy / u_window_size);

  float wave_x = cos(uv.x * frequency * aspect_ratio) * 0.5 + 0.5;
  float stripes_x = step(0.5, wave_x);

  float wave_y = cos(uv.y * frequency) * 0.5 + 0.5;
  float stripes_y = step(0.5, wave_y);

  float squares = stripes_x * stripes_y;

  fragColor = vec4(squares, squares,squares,1.0);

}
