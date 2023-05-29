#version 410 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D udepthMap;

void main()
{             
    float depthValue = texture(udepthMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
}  