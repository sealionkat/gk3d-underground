#version 330 core

#define POINT_LIGHTS_NR 2
#define SPOT_LIGHTS_NR 2

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight 
{
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};


struct SpotLight
{
    vec3 position;
    vec3 direction;
    vec3 color;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};


out vec4 color;

in vec3 FragPos;
in vec3 Normal;

uniform PointLight pointLights[POINT_LIGHTS_NR];

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;
uniform SpotLight spotLight;


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
  float distance = length(light.position - fragPos);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  // Ambient
  vec3 ambient = light.color * material.ambient;

  // Diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(normal, lightDir), 0.0f);
  vec3 diffuse = light.color * (diff * material.diffuse);

  // Specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.color * (material.specular * spec);

  return (ambient + diffuse + specular) * attenuation;  
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Ambient
    vec3 ambient = light.color * material.ambient;

    // Diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.color * (diff * material.diffuse);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.color * (material.specular * spec);

    // Edges
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);


    return (ambient + diffuse + specular) * attenuation * intensity /** attenuation * intensity*/;  
}


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < POINT_LIGHTS_NR; ++i) {
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    }
    result += CalculateSpotLight(spotLight, norm, FragPos, viewDir);

   result *= objectColor;

    color = vec4(result, 1.0f);
}
