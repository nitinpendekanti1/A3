#version 120

varying vec3 vPos; // Position in view space from vertex shader
varying vec3 vNor; // Normal in view space from vertex shader

void main() {
    vec3 eyeVector = normalize(-vPos); // Direction from fragment to camera in view space
    float dotProduct = abs(dot(normalize(vNor), eyeVector)); // Absolute value of dot product between normal and eye vector
    
    if(dotProduct < 0.3) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black
    } else {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White
    }
}
