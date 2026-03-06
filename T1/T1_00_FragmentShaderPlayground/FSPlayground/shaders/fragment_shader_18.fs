#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  
  vec3 pacman_color = vec3(1.0,1.0,0.0);
  vec3 bck_color = vec3(0.87,0.89,0.808);

  //Pixelado:
  float num_pixels = 1.0;
  float r = 1.0/num_pixels;
  vec2 window_size = u_window_size * r;
  vec2 fragCoord = round(gl_FragCoord.xy * r);
  
  //Pfffiuuuu:
  float wave_amplitude = 20.0;
  float pfiu_multiplier = 10.0;
  float offset_pfiu = sin(gl_FragCoord.x / u_window_size.x * 6.28 * pfiu_multiplier + u_time * 0.01) * wave_amplitude;

  //Body:
  vec2 body_center = vec2(window_size.x * 0.5, window_size.y * 0.5 + offset_pfiu);
  float body_radius = 180.0 * r;

  float body_distance = length(fragCoord.xy - body_center);
  float bs = step(body_distance, body_radius);

  //Eye
  float eye_radius = 30.0 * r;
  float eye_angle = 1.1;
  float eye_distance_to_center = 100.0 * r;
  vec2 eye_center = vec2(cos(eye_angle), sin(eye_angle)) * eye_distance_to_center + body_center;
  
  float eye_distance = length(fragCoord.xy - eye_center);
  float es = step(eye_radius, eye_distance);

  //Mouth:
  float mouth_angle = 0.85 + (cos(u_time * 0.01) * 0.075 + 0.075);
  float mouth_dir_angle = 0.0;
  vec2 mouth_dir = vec2(cos(mouth_dir_angle), sin(mouth_dir_angle));
  vec2 pixel_dir = normalize(fragCoord.xy - body_center);
  float mouth_dot = dot(mouth_dir, pixel_dir);
  float ms = step(mouth_dot, mouth_angle);

  //Final color:
  vec3 color = mix(bck_color, pacman_color, es * bs * ms);

  fragColor = vec4(color, 1.0);

}
