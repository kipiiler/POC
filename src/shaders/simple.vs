#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 uModelMat = mat4(
   0.5, 0.0, 0.0, 0.0,
   0.0, 0.5, 0.0, 0.0,
   0.0, 0.0, 0.5, 0.0,
   0.0, 0.0, 0.0, 1.0
);

void main()
{
   gl_Position = uModelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
