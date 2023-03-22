#version 440 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

layout (location = 0) uniform mat4 ModelView;
layout (location = 1) uniform mat4 Projection;
layout (location = 2) uniform mat3 NormalMatrix;

out vec3 fPosition;
out vec3 fNormal;

void getCamSpace(out vec3 norm, out vec3 position) {
    norm = normalize(NormalMatrix * vNormal);
    position = (ModelView * vec4(vPosition, 1.0)).xyz;
}

void main() {
    vec3 pos, norm;

    getCamSpace(norm, pos);

    fNormal = norm;
    fPosition = pos;
    gl_Position = Projection * vec4(pos, 1);
}