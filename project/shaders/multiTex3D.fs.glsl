#version 330 core

in vec2 vFragTexture;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

out vec3 fFragTexture;

void main() {
 // fFragTexture = mix(vec3(texture(uTexture, vFragTexture).xyz), vec3(texture(uTexture2, vFragTexture).xyz), 0.9) ;
  fFragTexture = vec3(texture(uTexture, vFragTexture).xyz) + vec3(texture(uTexture2, vFragTexture).xyz) ;
}