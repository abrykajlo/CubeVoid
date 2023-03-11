#version 440 core

in vec3 fLightIntensity;

out vec4 fColor;

void main() {
    if (gl_FrontFacing) {
        fColor = vec4(fLightIntensity, 1.0);
    } else {
        fColor = vec4(1.0, 0.0, 1.0, 1.0);
    }
}