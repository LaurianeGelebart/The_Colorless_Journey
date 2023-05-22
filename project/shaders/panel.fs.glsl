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




void main()
{
    vec3 texture = vec3(texture(uTexture, vFragTexture).xyz) ;
    
    fFragColor = texture  ;
}