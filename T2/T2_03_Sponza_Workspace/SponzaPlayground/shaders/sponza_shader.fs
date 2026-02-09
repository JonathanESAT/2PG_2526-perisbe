#version 330

layout(location = 0) out vec4 fragColor;

uniform vec3 u_camera_position;
uniform vec3 u_albedo;

in vec3 normal;
in vec3 pos;

struct Light{
  int type; // 0: Directional; 1: Point; 2: Spot
  int enabled;

  vec3 pos;
  vec3 dir;

  vec3 diff_color;
  vec3 spec_color;
  float spec_shininess;

  //atenuacion point y spot
  float constant;
  float linear;
  float quadratic;

  //spot_light (both cos)
  float inner_cutoff;
  float outer_cutoff;
};

vec3 g_ambient_color = vec3(0.0,0.6,1.0);
float g_ambient_strength = 0.1;

Light g_lights[8];

void InitLights() {
  // Sponza: X(-1921 a 1800), Y(-126 a 1429), Z(-1183 a 1105)

  // ------------------------------------------
  // LIGHT 0 - POINT roja (extremo izquierdo)
  // ------------------------------------------
  g_lights[0].enabled = 1;
  g_lights[0].type = 1;
  g_lights[0].pos = vec3(-1200.0, 500.0, 0.0);
  g_lights[0].dir = vec3(0.0);
  g_lights[0].diff_color = vec3(1.0, 0.1, 0.1);
  g_lights[0].spec_color = vec3(1.0, 0.3, 0.3);
  g_lights[0].spec_shininess = 64.0;
  g_lights[0].constant = 1.0;
  g_lights[0].linear = 0.0007;
  g_lights[0].quadratic = 0.000002;
  g_lights[0].inner_cutoff = 0.0;
  g_lights[0].outer_cutoff = 0.0;

  // ------------------------------------------
  // LIGHT 1 - POINT naranja (centro)
  // ------------------------------------------
  g_lights[1].enabled = 1;
  g_lights[1].type = 1;
  g_lights[1].pos = vec3(0.0, 500.0, 0.0);
  g_lights[1].dir = vec3(0.0);
  g_lights[1].diff_color = vec3(1.0, 0.6, 0.1);
  g_lights[1].spec_color = vec3(1.0, 0.7, 0.3);
  g_lights[1].spec_shininess = 64.0;
  g_lights[1].constant = 1.0;
  g_lights[1].linear = 0.0007;
  g_lights[1].quadratic = 0.000002;
  g_lights[1].inner_cutoff = 0.0;
  g_lights[1].outer_cutoff = 0.0;

  // ------------------------------------------
  // LIGHT 2 - POINT azul (extremo derecho)
  // ------------------------------------------
  g_lights[2].enabled = 1;
  g_lights[2].type = 1;
  g_lights[2].pos = vec3(1200.0, 500.0, 0.0);
  g_lights[2].dir = vec3(0.0);
  g_lights[2].diff_color = vec3(0.1, 0.3, 1.0);
  g_lights[2].spec_color = vec3(0.3, 0.5, 1.0);
  g_lights[2].spec_shininess = 64.0;
  g_lights[2].constant = 1.0;
  g_lights[2].linear = 0.0007;
  g_lights[2].quadratic = 0.000002;
  g_lights[2].inner_cutoff = 0.0;
  g_lights[2].outer_cutoff = 0.0;

  // ------------------------------------------
  // LIGHT 3 - POINT verde (lateral Z+)
  // ------------------------------------------
  g_lights[3].enabled = 1;
  g_lights[3].type = 1;
  g_lights[3].pos = vec3(0.0, 400.0, 800.0);
  g_lights[3].dir = vec3(0.0);
  g_lights[3].diff_color = vec3(0.1, 1.0, 0.2);
  g_lights[3].spec_color = vec3(0.3, 1.0, 0.4);
  g_lights[3].spec_shininess = 64.0;
  g_lights[3].constant = 1.0;
  g_lights[3].linear = 0.0007;
  g_lights[3].quadratic = 0.000002;
  g_lights[3].inner_cutoff = 0.0;
  g_lights[3].outer_cutoff = 0.0;

  // ------------------------------------------
  // LIGHT 4 - POINT magenta (lateral Z-)
  // ------------------------------------------
  g_lights[4].enabled = 1;
  g_lights[4].type = 1;
  g_lights[4].pos = vec3(0.0, 400.0, -800.0);
  g_lights[4].dir = vec3(0.0);
  g_lights[4].diff_color = vec3(1.0, 0.1, 0.8);
  g_lights[4].spec_color = vec3(1.0, 0.3, 0.9);
  g_lights[4].spec_shininess = 64.0;
  g_lights[4].constant = 1.0;
  g_lights[4].linear = 0.0007;
  g_lights[4].quadratic = 0.000002;
  g_lights[4].inner_cutoff = 0.0;
  g_lights[4].outer_cutoff = 0.0;

  // ------------------------------------------
  // LIGHT 5 - SPOT blanco (foco cenital centro)
  // ------------------------------------------
  g_lights[5].enabled = 1;
  g_lights[5].type = 2;
  g_lights[5].pos = vec3(0.0, 1400.0, 0.0);
  g_lights[5].dir = vec3(0.0, -1.0, 0.0);
  g_lights[5].diff_color = vec3(1.0, 1.0, 1.0);
  g_lights[5].spec_color = vec3(1.0, 1.0, 1.0);
  g_lights[5].spec_shininess = 32.0;
  g_lights[5].constant = 1.0;
  g_lights[5].linear = 0.0005;
  g_lights[5].quadratic = 0.000001;
  g_lights[5].inner_cutoff = cos(radians(20.0));
  g_lights[5].outer_cutoff = cos(radians(35.0));

  // ------------------------------------------
  // LIGHT 6 - SPOT cyan (foco izquierda)
  // ------------------------------------------
  g_lights[6].enabled = 1;
  g_lights[6].type = 2;
  g_lights[6].pos = vec3(-1000.0, 1200.0, 0.0);
  g_lights[6].dir = vec3(0.3, -1.0, 0.0);
  g_lights[6].diff_color = vec3(0.1, 1.0, 1.0);
  g_lights[6].spec_color = vec3(0.3, 1.0, 1.0);
  g_lights[6].spec_shininess = 64.0;
  g_lights[6].constant = 1.0;
  g_lights[6].linear = 0.0005;
  g_lights[6].quadratic = 0.000001;
  g_lights[6].inner_cutoff = cos(radians(15.0));
  g_lights[6].outer_cutoff = cos(radians(30.0));

  // ------------------------------------------
  // LIGHT 7 - SPOT amarillo (foco derecha)
  // ------------------------------------------
  g_lights[7].enabled = 1;
  g_lights[7].type = 2;
  g_lights[7].pos = vec3(1000.0, 1200.0, 0.0);
  g_lights[7].dir = vec3(-0.3, -1.0, 0.0);
  g_lights[7].diff_color = vec3(1.0, 1.0, 0.1);
  g_lights[7].spec_color = vec3(1.0, 1.0, 0.3);
  g_lights[7].spec_shininess = 64.0;
  g_lights[7].constant = 1.0;
  g_lights[7].linear = 0.0005;
  g_lights[7].quadratic = 0.000001;
  g_lights[7].inner_cutoff = cos(radians(15.0));
  g_lights[7].outer_cutoff = cos(radians(30.0));
}

vec3 DirectionalLight(Light light){
  vec3 norm = normalize(normal);
  // Diffuse:
  vec3 light_dir = normalize(-light.dir);
  float diff_dot = max(dot(norm, light_dir), 0.0);
  vec3 diff_color = diff_dot * light.diff_color;

  // Specular (Blinn-Phong):
  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(norm, halfway_dir), 0.0),
                    light.spec_shininess);
  vec3 spec_color = spec * light.spec_color;

  // Color:
  return diff_color + spec_color;
}

vec3 PointLight(Light light){
  vec3 norm = normalize(normal);
  // Diffuse:
  vec3 light_dir = normalize(light.pos - pos);
  float diff_dot = max(dot(norm, light_dir), 0.0);
  vec3 diff_color = diff_dot * light.diff_color;

  // Specular (Blinn-Phong):
  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(norm, halfway_dir), 0.0),
                    light.spec_shininess);
  vec3 spec_color = spec * light.spec_color;

  float distance = length(light.pos - pos);
  float attenuation = 1.0 / (light.constant +
                           light.linear * distance +
                           light.quadratic * distance * distance);
  return (diff_color + spec_color) * attenuation;
}


vec3 SpotLight(Light light){
  vec3 norm = normalize(normal);

  vec3 light_dir = normalize(light.pos - pos);

  // --- CÁLCULO DEL CONO DE LUZ ---
  float theta = dot(light_dir, normalize(-light.dir));
  float epsilon = light.inner_cutoff - light.outer_cutoff;
  float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);

  if(theta < light.outer_cutoff) {
    return vec3(0.0);
  }

  // --- DIFFUSE ---
  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light.diff_color;

  // --- SPECULAR (Blinn-Phong) ---
  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(norm, halfway_dir), 0.0), light.spec_shininess);
  vec3 specular = spec * light.spec_color;

  // --- ATENUACIÓN ---
  float distance = length(light.pos - pos);
  float attenuation = 1.0 / (light.constant +
                              light.linear * distance +
                              light.quadratic * distance * distance);

  return (diffuse + specular) * intensity * attenuation;
}

void main() {
  InitLights();
    // --- AMBIENT (luz global mínima) ---
  vec3 ambient = g_ambient_strength * g_ambient_color;
  
  // --- ACUMULACIÓN DE LUCES ---
  vec3 lighting = vec3(0.0);

  for(int i = 0; i < 8; ++i){
    if(g_lights[i].enabled == 0) continue;
    switch(g_lights[i].type){
      case 0: // Directional
        lighting += DirectionalLight(g_lights[i]);
        break;
      case 1: // Point
        lighting += PointLight(g_lights[i]);
        break;
      case 2: // Spot
        lighting += SpotLight(g_lights[i]);
        break;
    }
  }

  // --- COLOR FINAL ---
  // Combinar ambient + luces, multiplicar por color base del objeto
  vec3 albedo = vec3(0.8, 0.8, 0.8); // Gris claro (o usa u_albedo si lo pasas)
  vec3 final_color = (ambient + lighting) * albedo;
  
  // Clamp para evitar valores > 1.0 (sobreexposición)
  final_color = clamp(final_color, 0.0, 1.0);
  
  fragColor = vec4(final_color, 1.0);
}