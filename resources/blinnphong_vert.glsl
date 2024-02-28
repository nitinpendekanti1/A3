#version 120

uniform mat4 P;
uniform mat4 MV;

attribute vec4 aPos; // in object space
attribute vec3 aNor; // in object space

varying vec3 vertexPositionCameraSpace;
varying vec3 vertexNormalCameraSpace;

void main()
{
    gl_Position = P * MV * aPos;
    
    // Transform vertex position and normal to camera space
    vec4 vertexPositionWorldSpace = MV * aPos;
    vertexPositionCameraSpace = vertexPositionWorldSpace.xyz;
    
    vec4 vertexNormalWorldSpace = MV * vec4(aNor, 0.0);
    vertexNormalCameraSpace = normalize(vertexNormalWorldSpace.xyz);
}
