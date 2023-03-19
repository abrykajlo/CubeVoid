#version 440 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

layout (location = 0) uniform mat4 ModelView;
layout (location = 1) uniform mat4 Projection;
layout (location = 2) uniform mat3 NormalMatrix;

uniform struct LightInfo {
    vec4 Position;
    vec3 La;
    vec3 Ld;
    vec3 Ls;
} Light;

uniform struct MaterialInfo {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
} Material;

out vec3 fIntensity;

void main() {
    vec3 Ia = Light.La * Material.Ka;

    vec4 camCoords = ModelView * vec4(vPosition, 1.0);
    vec3 s = normalize(Light.Position - camCoords).xyz;
    vec3 n = normalize(NormalMatrix * vNormal);
    vec3 Id = Light.Ld * Material.Kd * max(dot(s, n), 0);
    
    vec3 r = -s + 2 * max(dot(s, n), 0) * n;
    vec3 v = vec3(0, 0, 1); // non-local viewer
    vec3 Is = Light.Ls * Material.Ks * pow(max(dot(r, v), 0), 6);

    fIntensity = Ia + Id + Is;
    //I /= max(max(I.x, I.y), I.z);
    gl_Position = Projection * camCoords;
}