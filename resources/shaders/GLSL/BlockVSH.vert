//Basic "Block" vertex shader

#version 410 core


//Input

//In vertex position (-1.f - 1.f)
layout(location = 0) in vec3 InPosition;
//layout(location = 1) in vec2 InUV;

//Output
//out vec4 OutColour;
//out vec2 OutUV;


//Uniform
uniform mat4 MatWorld;
uniform mat4 MatView;
uniform mat4 MatProj;

void main()
{
    gl_Position = MatProj * MatView * MatWorld * vec4(InPosition, 1.f);

}