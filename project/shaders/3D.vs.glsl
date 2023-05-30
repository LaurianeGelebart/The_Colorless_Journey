#version 410

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexture;

uniform mat4 uMVMatrix;
uniform mat4 uMVPMatrix;
uniform mat4 uNormalMatrix;
uniform mat4 lightSpaceMatrix;

out vec2 vFragTexture;
out vec3 vNormal_vs;
out vec3 vPosition_vs;
out vec4 FragPosLightSpace;

void main()
{
    vPosition_vs      = (uMVMatrix * vec4(aVertexPosition, 1)).xyz;
    vNormal_vs        = (uNormalMatrix * vec4(aVertexNormal, 1)).xyz;
    vFragTexture      = aVertexTexture;
    FragPosLightSpace = lightSpaceMatrix * vec4(vPosition_vs, 1.0);

    gl_Position = uMVPMatrix * vec4(aVertexPosition, 1);
};
