#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

/*
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
  if(dist_eye < eye_radius){
    color = background_color;
  }

  fragColor = vec4(color, 1.0);














*/

float DrawPackman(vec2 body_center, float body_radius, float eye_radius, float face_angle, float eye_d){

  //body
  float bl = length(gl_FragCoord.xy - body_center);
  float bc = step(bl, body_radius);

  //eye
  float eye_angle = 1.1;
  vec2 eye_center = vec2(cos(eye_angle) * eye_d, sin(eye_angle) * eye_d) + body_center;
  float el = length(gl_FragCoord.xy - eye_center);
  float ec = step(eye_radius, el);

  //mouth
  float mouth_angle = 0.78;
  float mouth_threshold = 0.7 + (sin(u_time * 0.01) * 0.15 + 0.15);
  vec2 face_dir = vec2(cos(face_angle), sin(face_angle));
  vec2 mouth_dir = vec2(cos(mouth_angle), sin(mouth_angle));
  vec2 pixel_dir = normalize(gl_FragCoord.xy - body_center);
  float mouth_dot = dot(pixel_dir, face_dir);
  float sd = step(mouth_dot,mouth_threshold);

  return bc * ec * sd;
}

void main() {
  vec3 packman_color = vec3(1,1,0);
  vec3 bgcolor = vec3(0.898, 0.949, 0.851);

  //packman 1
  vec2 body_center_01 = vec2(u_window_size.x * 0.25, u_window_size.y * 0.5);
  float pacman_01 = DrawPackman(body_center_01, 250.0, 30.0, 0, 150.0);

  //packman 2
  vec2 body_center_02 = vec2(u_window_size.x * 0.75, u_window_size.y * 0.5);
  float pacman_02 = DrawPackman(body_center_02, 150.0, 20.0, 1.57, 100.0);

  vec3 color = mix(bgcolor, packman_color,pacman_01);
  color = mix(color, packman_color,pacman_02);


  fragColor = vec4(color, 1.0);

}



