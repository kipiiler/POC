#version 330 core

out vec4 FragColor;
uniform vec3 uCol = vec3(1.0f, 0.5f, 0.2f);

void main() { FragColor = vec4(uCol, 1.0f); }
