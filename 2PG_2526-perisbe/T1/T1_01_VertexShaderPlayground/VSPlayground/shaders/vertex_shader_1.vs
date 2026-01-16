#version 330

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;
out vec2 uv;
uniform vec2 u_window_size;
uniform vec3 u_camera_position;
uniform float u_time;

//By default, in this demo the camera is in the following position:
//0.0, 2.0, 3.0
//By default, in this demo the object is in the following position:
//0.0, 0.0, 0.0
//By default, in this demo the window has the following size:
//1000.0, 600.0

//Example of function which returns a translation matrix:
mat4 InitAsTranslate(float tx, float ty, float tz) {
  return mat4(1.0, 0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0,
              0.0, 0.0, 1.0, 0.0,
              tx,  ty,  tz,  1.0);
}

mat4 InitAsScale(float sx, float sy, float sz) {
  return mat4( sx, 0.0, 0.0, 0.0,
              0.0,  sy, 0.0, 0.0,
              0.0, 0.0,  sz, 0.0,
              0.0, 0.0, 0.0, 1.0);
}

mat4 InitAsRotate(vec3 axis, float angle) {
  vec3 ax = normalize(axis);
  float s = sin(angle);
  float c = cos(angle);
  float oc = 1.0 - c;

  float m_00 = oc * axis.x * axis.y + c;
  float m_01 = oc * axis.x * axis.y - axis.z * s;
  float m_02 = oc * axis.x * axis.z + axis.y * s;

  float m_04 = oc * axis.x * axis.y + axis.z * s;
  float m_05 = oc * axis.y * axis.y + c;
  float m_06 = oc * axis.y * axis.z + axis.x * s;

  float m_08 = oc * axis.x * axis.z + axis.y * s;
  float m_09 = oc * axis.y * axis.z + axis.x * s;
  float m_10 = oc * axis.z * axis.z + c;

  return mat4( m_00, m_01, m_02, 0.0,
               m_04, m_05, m_06, 0.0,
               m_08, m_09, m_10, 0.0,
                0.0,  0.0,  0.0, 1.0);
}

mat4 InitAsView(vec3 target, vec3 cam_pos, vec3 up) {
  vec3 forward = normalize(target - cam_pos);
  vec3 left = normalize(cross(forward, up));
  vec3 updated_up = normalize(cross(left, forward));

  float dot_left_pos = dot(left, cam_pos);
  float dot_up_pos = dot(updated_up, cam_pos);
  float dot_fwd_pos = dot(forward, cam_pos);

  return mat4(       left.x,    updated_up.x,     -forward.x,      0.0,
                     left.y,    updated_up.y,     -forward.y,      0.0,
                     left.z,    updated_up.z,     -forward.z,      0.0,
              -dot_left_pos,     -dot_up_pos,    dot_fwd_pos,      1.0);
}

mat4 InitAsPerspective(float fov, float z_near, float z_far) {
  float r = tan(fov * 0.5);
  float aspect_ratio = u_window_size.x / u_window_size.y;

  float m_00 = 1.0 / (aspect_ratio * r);
  float m_05 = 1.0 / r;
  float m_10 = -(z_far + z_near) / (z_far + z_near);
  float m_14 = -(2.0 * z_far * z_near) / (z_far - z_near);

  return mat4(m_00,  0.0,  0.0,  0.0,
               0.0, m_05,  0.0,  0.0,
               0.0,  0.0, m_10, -1.0,
               0.0,  0.0, m_14,  0.0);
}

mat4 InitAsOrtho(float left, float right, float top, float bottom,
                 float near, float far) {
  float m_00 = 2.0 / (right - left);
  float m_05 = -2.0 / (top - bottom);
  float m_10 = -2.0 / (far - near);
  float m_12 = -(right + left) / (right - left);
  float m_13 = -(top + bottom) / (top - bottom);
  float m_14 = -(far + near) / (far - near);

  return mat4( m_00,  0.0,  0.0, 0.0,
                0.0, m_05,  0.0, 0.0,
                0.0,  0.0, m_10, 0.0,
               m_12, m_13, m_14, 1.0);

}

void main(){

  mat4 model = InitAsTranslate(0.0,0.0,0.0);
  mat4 view = InitAsView(vec3(0.0,0.0,0.0), u_camera_position, vec3(0.0,1.0,0.0));
  mat4 projection = InitAsPerspective(1.57, 0.1, 100.0);

  gl_Position = projection * view * model * vec4(a_position, 1.0);
  uv = a_uv;
}
