#version 440 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

out vec3 fLightIntensity;

layout (location = 0) uniform mat4 ModelView;
layout (location = 1) uniform mat4 Projection;
layout (location = 2) uniform mat3 NormalMatrix;

vec4 LightPosition = vec4(1, 1, 1, 1);
vec3 Kd = vec3(1, 0, 0);
vec3 Ld = vec3(0.8, 0.8, 0.8);

void main() {
    vec4 camCoords = ModelView * vec4(vPosition, 1.0);
    vec3 s = normalize(LightPosition - camCoords).xyz;
    vec3 normal = NormalMatrix * vNormal;
    fLightIntensity = Ld * Kd * max(dot(s, normal), 0.0);
    gl_Position = Projection * camCoords;
}