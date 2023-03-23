#version 440 core

float PI = 3.14159265358979;

uniform struct LightInfo {
    vec4 Position;
    vec3 L;
} Light[3];

uniform struct MaterialInfo {
    float Roughness;
    bool Metal;
    vec3 Color;
} Material;

in vec3 fPosition;
in vec3 fNormal;

out vec4 fColor;

vec3 schlickFresnel(float lDotH) {
    vec3 f0 = vec3(0.04); // dielectrics
    if (Material.Metal) {
        f0 = Material.Color;
    }
    return f0 + (1 - f0) * pow(1.0 - lDotH, 5);
}

float geomSmith(float nDotV) {
    float k = (Material.Roughness + 1.0) * (Material.Roughness + 1.0) / 8;
    float denom = nDotV * (1 - k) + k;
    return 1.0 / denom;
}

float ggxDistribution(float nDotH) {
    float alpha2 = Material.Roughness * Material.Roughness * Material.Roughness * Material.Roughness;
    float d = (nDotH * nDotH) * (alpha2 - 1) + 1;
    return alpha2 / (PI * d * d);
}

vec3 microfacetModel(int i, vec3 position, vec3 n) {
    vec3 diffuseBrdf = vec3(0.0); // Metal
    if (!Material.Metal) {
        diffuseBrdf = Material.Color;
    }

    vec3 l = Light[i].Position.xyz - position;
    float dist2 = dot(l, l);
    l = normalize(l);
    vec3 lightl = Light[i].L / dist2;

    vec3 v = normalize(-position);
    vec3 h = normalize(v + l);
    float nDotH = dot(n, h);
    float nDotV = dot(n, v);
    float lDotH = dot(l, h);
    float nDotL = max(dot(n, l), 0);
    vec3 specBdrf = 0.25 * ggxDistribution(nDotH) * schlickFresnel(lDotH) * geomSmith(nDotL) * geomSmith(nDotV);

    return (diffuseBrdf + PI * specBdrf) * lightl * nDotL;
}

void main() {
    vec3 Intensity = vec3(0);
    vec3 n = normalize(fNormal);
    
    for (int i = 0; i < 3; i++) {
        Intensity += microfacetModel(i, fPosition, n);
    }

    // Gamma correction
    Intensity = pow(Intensity, vec3(1.0/2.2));

    fColor = vec4(Intensity, 1);
}