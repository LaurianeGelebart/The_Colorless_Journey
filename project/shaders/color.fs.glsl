#version 410

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vFragTexture;

uniform vec3  uKd;
uniform vec3  uKs;
uniform float uShininess;

uniform vec3 uLightMagic_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

void main()
{
    vec3  w0         = normalize(-vPosition_vs);
    vec3  wi         = normalize(uLightMagic_vs - vPosition_vs);
    vec3  halfVector = (w0 + wi) / 2.0;
    float nDotL      = max(0.0, dot(wi, vNormal_vs));

    vec3  diffuse = uKd * nDotL;
    float d       = distance(vPosition_vs, uLightMagic_vs);

    vec3 light = (uLightIntensity / (d * d)) * (diffuse);

    fFragColor = uKd * 0.9 + 0.1 * light;
}