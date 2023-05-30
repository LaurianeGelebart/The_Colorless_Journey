#version 410

in vec2 vFragTexture;

uniform sampler2D uTexture;

out vec3 fFragColor;

void main()
{
    vec3 texture = vec3(texture(uTexture, vFragTexture).xyz);

    fFragColor = texture;
}