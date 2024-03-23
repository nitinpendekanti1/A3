#version 120

uniform mat4 P; // Projection matrix
uniform mat4 MV; // Model-view matrix
uniform mat3 N; // Normal matrix for transforming normals

attribute vec4 aPos; // Vertex position in object space
attribute vec3 aNor; // Vertex normal in object space

varying vec3 vPos; // Position in view space for fragment shader
varying vec3 vNor; // Normal in view space for fragment shader

void main() {
    vec4 viewPos = MV * aPos; // Transform vertex position to view space
    vPos = viewPos.xyz; // Pass view space position to fragment shader
    vNor = normalize(N * aNor); // Transform normal to view space and normalize
    gl_Position = P * viewPos; // Project vertex to clip space
}
