#version 120

uniform vec3 lightPos;
uniform vec3 ka; // ambient color
uniform vec3 kd; // diffuse color
uniform vec3 ks; // specular color
uniform float s; // shininess

varying vec3 vertexPositionCameraSpace;
varying vec3 vertexNormalCameraSpace;

void main()
{
    // Compute normalized normal vector
    vec3 n = normalize(vertexNormalCameraSpace);
    
    // Compute light vector (direction from fragment to light source)
    vec3 lightDir = normalize(lightPos - vertexPositionCameraSpace);
    
    // Compute view vector (direction from fragment to camera)
    vec3 viewDir = normalize(-vertexPositionCameraSpace);
    
    // Compute halfway vector between light and view vectors (Blinn-Phong)
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    // Compute diffuse component
    float diffuseIntensity = max(0.0, dot(lightDir, n));
    vec3 diffuseColor = kd * diffuseIntensity;
    
    // Compute specular component
    float specularIntensity = pow(max(0.0, dot(halfwayDir, n)), s);
    vec3 specularColor = ks * specularIntensity;
    
    // Final color (ambient + diffuse + specular)
    vec3 ambientColor = ka;
    vec3 finalColor = ambientColor + diffuseColor + specularColor;
    
    gl_FragColor = vec4(finalColor, 1.0);
}
