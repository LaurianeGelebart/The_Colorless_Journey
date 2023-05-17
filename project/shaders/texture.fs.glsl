#version 410

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vFragTexture;

uniform  vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs; 
uniform vec3 uLightCharacter_vs; 
uniform vec3 uLightDir_vs; 
uniform vec3 uLightIntensity;

uniform sampler2D uTexture; 


out vec3 fFragColor;


vec3 blinnPhongDir()
{
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightDir_vs);
    vec3 halfVector = (w0 + wi)/2.0;
    float nDotL = max(0.0, dot(wi, vNormal_vs));
    float nDotH = max(0.0, dot(halfVector, vNormal_vs));
    float specular = pow(nDotH, (1.0));
    vec3 diffuse = vec3(1.0) * nDotL;
    vec3 specularColor = uKs * specular;

    return uLightIntensity * (diffuse + specularColor);
}

vec3 blinnPhongPos()
{
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    vec3 halfVector = (w0 + wi)/2.0;
    float nDotL = max(0.0, dot(wi, vNormal_vs));
    float nDotH = max(0.0, dot(halfVector, vNormal_vs));
    float specular = pow(nDotH, 1.0);
    vec3 diffuse = vec3(0.5) * nDotL;
    vec3 specularColor = uKs * specular;
    float d = distance(vPosition_vs,uLightPos_vs);

    return (uLightIntensity / (d * d)) * (diffuse + specularColor);
}

vec3 blinnPhongPosCharacter()
{
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    vec3 halfVector = (w0 + wi)/2.0;
    float nDotL = max(0.0, dot(wi, vNormal_vs));
    float nDotH = max(0.0, dot(halfVector, vNormal_vs));
    float specular = pow(nDotH, 1.0);
    vec3 diffuse = vec3(0.5) * nDotL;
    vec3 specularColor = vec3(1.0 , 0.7 , 0.0 ) * specular;
    float d = distance(vPosition_vs,uLightCharacter_vs);

    return (0.1 / (d * d)) * (diffuse + specularColor);
}

void main()
{
    //fFragColor = uKd; 

    vec3 lightDir = blinnPhongDir();

    vec3 lightPos = blinnPhongPos();
    vec3 lightCharacter = blinnPhongPosCharacter();
    vec3 texture = vec3(texture(uTexture, vFragTexture).xyz) ;
    
    //fFragColor = lightCharacter * texture ;
    fFragColor = texture * (lightPos + lightCharacter) ;
}