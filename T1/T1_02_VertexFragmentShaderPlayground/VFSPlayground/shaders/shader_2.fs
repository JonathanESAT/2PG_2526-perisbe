#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec3 v_normal;


void main() {
  if(v_normal.z > 0.5)
  {
    fragColor = vec4(1.0,0.0,0.0,1.0);
  }else
  {
    fragColor = vec4(0.0,0.0,0.0,1.0);
  }
}
