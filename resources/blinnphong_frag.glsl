#version 120

uniform vec3 lightPos1;
uniform vec3 lightColor1;
uniform vec3 lightPos2;
uniform vec3 lightColor2;
uniform vec3 ka; // ambient color
uniform vec3 kd; // diffuse color
uniform vec3 ks; // specular color
uniform float s; // shininess

varying vec3 vertexPositionCameraSpace;
varying vec3 vertexNormalCameraSpace;

vec3 applyLight(vec3 lightPos, vec3 lightColor, vec3 vertexPos, vec3 normal, vec3 kd, vec3 ks, float shininess) {
    // Compute light vector (direction from fragment to light source)
    vec3 lightDir = normalize(lightPos - vertexPos);
    
    // Compute view vector (direction from fragment to camera)
    vec3 viewDir = normalize(-vertexPos);
    
    // Compute halfway vector between light and view vectors (Blinn-Phong)
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    // Compute diffuse component
    float diffuseIntensity = max(0.0, dot(lightDir, normal));
    vec3 diffuse = kd * diffuseIntensity;
    
    // Compute specular component
    float specularIntensity = pow(max(0.0, dot(halfwayDir, normal)), shininess);
    vec3 specular = ks * specularIntensity;
    
    // Multiply each component by the light's color
    return (ka + diffuse + specular) * lightColor;
}

void main() {
    // Compute normalized normal vector
    vec3 n = normalize(vertexNormalCameraSpace);

    // Apply first light
    vec3 color1 = applyLight(lightPos1, lightColor1, vertexPositionCameraSpace, n, kd, ks, s);

    // Apply second light
    vec3 color2 = applyLight(lightPos2, lightColor2, vertexPositionCameraSpace, n, kd, ks, s);

    // Sum up the light contributions
    vec3 finalColor = color1 + color2;
    
    // Set the final color output
    gl_FragColor = vec4(finalColor, 1.0);
}
