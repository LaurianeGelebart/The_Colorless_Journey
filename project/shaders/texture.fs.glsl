#version 410 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vFragTexture;
in vec4 FragPosLightSpace;

uniform vec3  uKd;
uniform vec3  uKs;
uniform float uShininess;

uniform vec3 uLightPuits_vs     = vec3(0.0);
uniform vec3 uLightHouse_vs     = vec3(0.0);
uniform vec3 uLightMagic_vs     = vec3(0.0);
uniform vec3 uLightCharacter_vs = vec3(0.0);
uniform vec3 uLightDir_vs       = vec3(0.2);
uniform vec3 uLightIntensity    = vec3(0.0);

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 viewPos;

uniform sampler2D uTexture;

out vec3 fFragColor;

vec3 blinnPhongDir()
{
    vec3  w0            = normalize(-vPosition_vs);
    vec3  wi            = normalize(uLightDir_vs);
    vec3  halfVector    = (w0 + wi) / 2.0;
    float nDotL         = max(0.0, dot(wi, vNormal_vs));
    float nDotH         = max(0.0, dot(halfVector, vNormal_vs));
    float specular      = pow(nDotH, (1.0));
    vec3  diffuse       = vec3(0.5) * nDotL;
    vec3  specularColor = uKs * specular;

    return uLightIntensity * (diffuse + specularColor);
}

vec3 blinnPhongPosCharacter()
{
    vec3  w0            = normalize(-vPosition_vs);
    vec3  wi            = normalize(uLightCharacter_vs - vPosition_vs);
    vec3  halfVector    = (w0 + wi) / 2.0;
    float nDotL         = max(0.0, dot(wi, vNormal_vs));
    float nDotH         = max(0.0, dot(halfVector, vNormal_vs));
    float specular      = pow(nDotH, 1.0);
    vec3  diffuse       = vec3(0.5) * nDotL;
    vec3  specularColor = vec3(1.0, 0.7, 0.0) * specular;
    float d             = distance(vPosition_vs, uLightCharacter_vs);

    return (0.02 / (d * d)) * (diffuse + specularColor);
}

vec3 blinnPhongPos(vec3 uLight_vs)
{
    vec3  w0            = normalize(-vPosition_vs);
    vec3  wi            = normalize(uLight_vs - vPosition_vs);
    vec3  halfVector    = (w0 + wi) / 2.0;
    float nDotL         = max(0.0, dot(wi, vNormal_vs));
    float nDotH         = max(0.0, dot(halfVector, vNormal_vs));
    float specular      = pow(nDotH, 1.0);
    vec3  diffuse       = vec3(0.5) * nDotL;
    vec3  specularColor = vec3(1.0, 0.8, 0.4) * specular;
    float d             = distance(vPosition_vs, uLight_vs);

    return (uLightIntensity / (d * d)) * (diffuse + specularColor);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    vec3 lightDir       = blinnPhongDir();
    vec3 lightCharacter = blinnPhongPosCharacter();

    vec3 lightMagic = blinnPhongPos(uLightMagic_vs);
    vec3 lightHouse = blinnPhongPos(uLightHouse_vs);
    vec3 lightPuits = blinnPhongPos(uLightPuits_vs);

    vec3 texture = vec3(texture(uTexture, vFragTexture).xyz);

    // float shadow = ShadowCalculation(FragPosLightSpace);
    // vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    fFragColor = texture * (0.3 * lightCharacter +  0.4 * lightHouse + 0.05 * lightPuits + 0.05 * lightMagic + 2.0 * lightDir);
}