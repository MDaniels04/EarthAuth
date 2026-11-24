#Basic "Block" vertex shader

#version 410 core


//Input
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InUV;

//Output
out vec4 OutColour;
out vec4 OutUV;


//Uniform
uniform mat4 MatWorld;
uniform mat4 MatView;
uniform mat4 MatProj;

void main()
{
    gl_Position = MatWorld * vec4(InPosition, 1.0);
    gl_Position *= MatView;
    gl_Position *= MatProj;

    OutUV = InUV;
}