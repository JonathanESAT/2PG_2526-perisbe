#version 330

//By default, in this demo the palace object is located in the following position:
//  0.0, 0.0, 0.0

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;
uniform vec3 u_camera_position;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

out vec3 normal;

void main() {
  gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);
  normal = a_normal * 0.5 + 0.5;
}
