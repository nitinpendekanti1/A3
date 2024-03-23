#version 120

// Lighting properties
uniform vec3 lightPos; // Position of the light source
uniform vec3 lightColor; // Color of the light source

// Material properties
uniform vec3 ka; // Ambient reflectivity
uniform vec3 kd; // Diffuse reflectivity
uniform vec3 ks; // Specular reflectivity
uniform float s; // Shininess

varying vec3 vPos; // Position in view space from vertex shader
varying vec3 vNor; // Normal in view space from vertex shader

// Function to quantize a color component based on the number of levels
float quantize(float value, int levels) {
    return floor(value * float(levels)) / float(levels - 1);
}

void main() {
    vec3 N = normalize(vNor); // Normalized normal vector
    vec3 eyeVector = normalize(-vPos); // Direction from fragment to camera in view space
    float intensity = abs(dot(N, eyeVector)); // Dot product for silhouette effect
    
    // Check for silhouette
    if(intensity < 0.3) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black silhouette
        return;
    }
    
    // Lighting calculations for non-silhouette areas
    vec3 L = normalize(lightPos - vPos); // Direction from surface point to light
    vec3 V = eyeVector; // Already calculated
    vec3 R = reflect(-L, N); // Reflected light vector

    // Ambient component
    vec3 ambient = ka * lightColor;

    // Diffuse component
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = kd * diff * lightColor;

    // Specular component
    float spec = pow(max(dot(V, R), 0.0), s);
    vec3 specular = ks * spec * lightColor;

    // Combine components
    vec3 color = ambient + diffuse + specular;

    // Apply quantization to each color component
    color.r = quantize(color.r, 5);
    color.g = quantize(color.g, 5);
    color.b = quantize(color.b, 5);

    gl_FragColor = vec4(color, 1.0);
}
