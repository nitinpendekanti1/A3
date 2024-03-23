#version 120

uniform mat4 P; // Projection matrix
uniform mat4 MV; // Model-view matrix
uniform mat3 N; // Normal matrix for transforming normals

attribute vec4 aPos; // Vertex position in object space
attribute vec3 aNor; // Vertex normal in object space

varying vec3 vPos; // Position in view space for fragment shader
varying vec3 vNor; // Normal in view space for fragment shader

void main() {
    // Transform vertex position to view space
    vec4 viewPos = MV * aPos;
    vPos = viewPos.xyz;

    // Transform normal to view space and normalize
    vNor = normalize(N * aNor);

    // Project vertex to clip space
    gl_Position = P * viewPos;
}
