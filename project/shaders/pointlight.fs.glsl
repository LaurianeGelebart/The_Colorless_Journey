#version 410

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform  vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs; 
uniform vec3 uLightIntensity;


out vec3 fFragColor;

vec3 blinnPhong()
{
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    vec3 halfVector = (w0 + wi)/2.0;
    float nDotL = max(0.0, dot(wi, vNormal_vs));
    float nDotH = max(0.0, dot(halfVector, vNormal_vs));
    float specular = pow(nDotH, uShininess);
    vec3 diffuse = uKd * nDotL;
    vec3 specularColor = uKs * specular;
    float d = distance(vPosition_vs,uLightPos_vs);

    return (uLightIntensity / (d * d)) * (diffuse + specularColor);
}


void main()
{
  // fFragColor = vec3(0.2,0.5,0.5); 
    fFragColor =  blinnPhong();
}