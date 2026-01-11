#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  vec2 uv = gl_FragCoord.xy / u_window_size;
  vec2 uv_remapped = uv;
  uv_remapped.x = (uv.x - 0.25) / 0.5;
  float dist1 = abs(uv_remapped.x - uv.y);
  float dist2 = abs((uv_remapped.x + uv.y) - 1.0);
  
  float line1 = smoothstep( 0.003, 0.0, dist1);
  float line2 = smoothstep( 0.003, 0.0, dist2);

  float mask_left = step(0.25, uv.x);
  float mask_right = step(uv.x, 0.75);

  float mask = mask_left * mask_right;

  float final_result = (line1 + line2) * mask;

  fragColor = vec4(final_result, final_result, 0.0, 1.0);
  
}
