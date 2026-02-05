#version 330

layout(location = 0) out vec4 fragColor;

uniform vec3 u_camera_position;

in vec3 normal;
in vec3 frag_pos;

// Material (hardcoded)
vec3 object_color = vec3(0.8, 0.2, 0.2);
float ambient_strength = 0.1;
float shininess = 32.0;

struct Light{
  int type; // 0: Directional; 1: Point; 2: Spot
  int enabled;
  vec3 pos;
  vec3 dir;
  vec3 diff_color;
  vec3 spec_color;
};

Light g_lights[1];

void InitLights() {
  g_lights[0].enabled = 1;
  g_lights[0].type = 1; // Point
  g_lights[0].pos = vec3(3.0, 3.0, 3.0);
  g_lights[0].dir = vec3(-1.0, 0.0, 0.0);
  g_lights[0].diff_color = vec3(1.0, 1.0, 1.0);
  g_lights[0].spec_color = vec3(1.0, 1.0, 1.0);
}

vec3 DirectionalLight(Light light){
  return vec3(0.0);
}

vec3 PointLight(Light light){
  vec3 norm = normalize(normal);

  // Ambiental
  vec3 ambient = ambient_strength * light.diff_color;

  // Difusa
  vec3 light_dir = normalize(light.pos - frag_pos);
  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light.diff_color;

  // Especular
  vec3 view_dir = normalize(u_camera_position - frag_pos);
  vec3 reflect_dir = reflect(-light_dir, norm);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
  vec3 specular = spec * light.spec_color;

  return (ambient + diffuse + specular) * object_color;
}

vec3 SpotLight(Light light){
  return vec3(0.0);
}

void main() {
  InitLights();
  vec3 color = vec3(0.0, 0.0, 0.0);

  for(int i = 0; i < 1; ++i){
    switch(g_lights[i].type){
      case 0:
        color += DirectionalLight(g_lights[i]);
        break;
      case 1:
        color += PointLight(g_lights[i]);
        break;
      case 2:
        color += SpotLight(g_lights[i]);
        break;
    }
  }
  fragColor = vec4(color, 1.0);
}
