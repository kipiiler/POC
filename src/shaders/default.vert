#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;

uniform mat4 uModelMat = mat4(1.0);
uniform mat4 uViewMat = mat4(1.0);
uniform mat4 uProjMat = mat4(1.0);

void main()
{
    gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}