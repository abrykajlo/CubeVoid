#version 440 core

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

in vec3 fPosition;
in vec3 fNormal;

out vec4 fColor;

vec3 phongModel(vec3 position, vec3 n) {
    vec3 ambient = Light.La * Material.Ka;

    vec3 s = normalize(Light.Position.xyz - position);
    vec3 diffuse = Light.Ld * Material.Kd * max(dot(s, n), 0);

    vec3 r = -s + 2 * max(dot(s, n), 0) * n;
    vec3 v = vec3(0, 0, 1); // non-local viewer

    vec3 specular = Light.Ls * Material.Ks * pow(max(dot(r, v), 0), 6);

    return ambient + diffuse + specular;
}

void main() {
    vec3 Intensity = phongModel(fPosition, fNormal);
    fColor = vec4(Intensity, 1);
}