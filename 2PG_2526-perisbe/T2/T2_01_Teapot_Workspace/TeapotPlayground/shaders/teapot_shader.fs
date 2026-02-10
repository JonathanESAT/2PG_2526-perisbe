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
float g_ambient_strength = 0.15;

Light g_lights[3];

void InitLights() {
  // ------------------------------------------
  //LIGHT 0 DIRECTIONAL
  // ------------------------------------------
  g_lights[0].enabled = 1;
  g_lights[0].type = 0; //directional
  g_lights[0].pos = vec3(0.0); //not use in dir
  g_lights[0].dir = vec3(-0.5, -1.0, -0.3); //arriba izq
  g_lights[0].diff_color = vec3(0.8, 0.8, 0.7); //calida tipo sol
  g_lights[0].spec_color = vec3(1.0, 1.0, 1.0);
  g_lights[0].spec_shininess = 32.0;
  //Atenuación no aplica a direccional
  g_lights[0].constant = 1.0;
  g_lights[0].linear = 0.0;
  g_lights[0].quadratic = 0.0;
  g_lights[0].inner_cutoff = 0.0;
  g_lights[0].outer_cutoff = 0.0;

  // ------------------------------------------
  //LIGHT 1 PTO
  // ------------------------------------------
  g_lights[1].enabled = 1;
  g_lights[1].type = 1; // Point
  g_lights[1].pos = vec3(2.0, 1.0, 2.0); //lightbulb pos
  g_lights[1].dir = vec3(0.0); //not used in point ligth
  g_lights[1].diff_color = vec3(1.0, 0.3, 0.3); //red
  g_lights[1].spec_color = vec3(1.0, 1.0, 1.0); 
  g_lights[1].spec_shininess = 64.0;
  //atenuation
  g_lights[1].constant = 1.0;
  g_lights[1].linear = 0.09;
  g_lights[1].quadratic = 0.032;
  g_lights[1].inner_cutoff = 0.0;
  g_lights[1].outer_cutoff = 0.0;


  // ------------------------------------------
  //LIGHT 2 FOCO
  // ------------------------------------------
  g_lights[2].enabled = 1;
  g_lights[2].type = 2; //spot
  g_lights[2].pos = vec3(-2.0, 3.0, 2.0);
  g_lights[2].dir = vec3(0.5, -1.0, -0.5);
  g_lights[2].diff_color = vec3(0.3, 0.3, 1.0); //blue
  g_lights[2].spec_color = vec3(1.0, 1.0, 1.0); 
  g_lights[2].spec_shininess = 64.0;
  //atenuation
  g_lights[2].constant = 1.0;
  g_lights[2].linear = 0.09;
  g_lights[2].quadratic = 0.032;
  // Cutoff angles (en cosenos para optimización)
  // cos(12.5°) = 0.9763, cos(17.5°) = 0.9537
  g_lights[2].inner_cutoff = cos(radians(12.5));
  g_lights[2].outer_cutoff = cos(radians(17.5));
}

vec3 DirectionalLight(Light light){
  vec3 color = vec3(0.0, 0.0, 0.0);
  // Diffuse:
  vec3 light_dir = normalize(-light.dir);
  float diff_dot = max(dot(normal, light_dir), 0.0);
  vec3 diff_color = diff_dot * light.diff_color;

  // Specular: 
  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 
                    light.spec_shininess);
  vec3 spec_color = spec * light.spec_color;

  // Color:
  color = diff_color + spec_color;
  return color;
}

vec3 PointLight(Light light){
  float light_distance = length(light.pos - pos);
  float att = 1.0 / (light.constant + light.linear * light_distance + light.quadratic * light_distance * light_distance);
  vec3 color = vec3(0.0, 0.0, 0.0);
  // Diffuse:
  vec3 light_dir = normalize(light.pos - pos);
  float diff_dot = max(dot(normal, light_dir), 0.0);
  vec3 diff_color = diff_dot * light.diff_color * att;

  // Specular: 
  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 
                    light.spec_shininess);
  vec3 spec_color = spec * light.spec_color * att;

  float distance = length(light.pos - pos);
  float attenuation = 1.0 / (light.constant + 
                           light.linear * distance + 
                           light.quadratic * distance * distance);
  color = (diff_color + spec_color) * attenuation;

  return color;
}


vec3 SpotLight(Light light){
  vec3 color = vec3(0.0, 0.0, 0.0);

  vec3 light_dir = normalize(light.pos - pos);

    // --- CÁLCULO DEL CONO DE LUZ ---
    // theta: ángulo entre la dirección del foco y el vector hacia el fragmento
  float theta = dot(light_dir, normalize(-light.dir));

  // epsilon: diferencia entre inner y outer para suavizar el borde
  float epsilon = light.inner_cutoff - light.outer_cutoff;

  // intensity: 1.0 dentro del cono interior, 0.0 fuera del exterior, gradiente entre ambos
  float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
  
  // Si estamos fuera del cono exterior, no hay iluminación
  if(theta < light.outer_cutoff) {
      return vec3(0.0);
  }

      // --- DIFFUSE ---
  float diff = max(dot(normal, light_dir), 0.0);
  vec3 diffuse = diff * light.diff_color;
  
  // --- SPECULAR ---
  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), light.spec_shininess);
  vec3 specular = spec * light.spec_color;
  
  // --- ATENUACIÓN ---
  float distance = length(light.pos - pos);
  float attenuation = 1.0 / (light.constant + 
                              light.linear * distance + 
                              light.quadratic * distance * distance);
  
  // --- RESULTADO ---
  // Aplicamos intensidad del cono Y atenuación por distancia
  color = (diffuse + specular) * intensity * attenuation;

  return color;
}

void main() {
  InitLights();
    // --- AMBIENT (luz global mínima) ---
  vec3 ambient = g_ambient_strength * g_ambient_color;
  
  // --- ACUMULACIÓN DE LUCES ---
  vec3 lighting = vec3(0.0);

  for(int i = 0; i < 3; ++i){
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