#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragColor;


void main() {

    outColor = vec4(cos(degrees(fragColor[0])), fragColor[1], fragColor[2], 1.0);
}