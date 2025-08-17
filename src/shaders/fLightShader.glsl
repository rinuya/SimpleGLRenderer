#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

#define MAX_LIGHTS 16

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

uniform int numDirLights;
uniform DirLight dirLights[MAX_LIGHTS];

uniform int numPointLights;
uniform PointLight pointLights[MAX_LIGHTS];

uniform int numSpotLights;
uniform SpotLight spotLights[MAX_LIGHTS];

uniform Material material;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 materialDiff, vec3 materialSpec);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 materialDiff, vec3 materialSpec);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 materialDiff, vec3 materialSpec);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 materialDiff = texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 materialSpec = texture(material.texture_specular1, TexCoords).rgb;

    vec3 texColor = vec3(0);

    // Apply directional lights
    for (int i = 0; i < numDirLights; i++) {
        texColor += CalcDirLight(dirLights[i], norm, viewDir, materialDiff, materialSpec);
    }
    // Apply point lights
    for (int i = 0; i < numPointLights; i++) {
        texColor += CalcPointLight(pointLights[i], norm, FragPos, viewDir, materialDiff, materialSpec);
    }
    // Apply spot lights 
    for (int i = 0; i < numSpotLights; i++) {
        texColor += CalcSpotLight(spotLights[i], norm, FragPos, viewDir, materialDiff, materialSpec);
    }

    FragColor = vec4(min(texColor, vec3(1.0)), 1.0);

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 materialDiff, vec3 materialSpec) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);

    // combine results
    vec3 ambient  = light.ambient  * materialDiff;
    vec3 diffuse  = light.diffuse  * diff * materialDiff;
    vec3 specular = light.specular * diff * spec * materialSpec;  

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 materialDiff, vec3 materialSpec) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * distance * distance);

    // combine results
    vec3 ambient  = light.ambient  * materialDiff;
    vec3 diffuse  = light.diffuse  * diff * materialDiff;
    vec3 specular = light.specular * diff * spec * materialSpec;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 materialDiff, vec3 materialSpec) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * distance * distance);

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine results
    vec3 ambient  = light.ambient  * materialDiff;
    vec3 diffuse  = light.diffuse  * diff * materialDiff;
    vec3 specular = light.specular * diff * spec * materialSpec;

    ambient  *= attenuation * intensity;
    diffuse  *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}