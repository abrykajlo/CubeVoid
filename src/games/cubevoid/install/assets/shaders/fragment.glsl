#version 440 core

in vec3 fIntensity;

out vec4 fColor;

void main() {
    fColor = vec4(fIntensity, 1);
}