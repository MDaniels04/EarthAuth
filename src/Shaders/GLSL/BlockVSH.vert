#Basic "Block" vertex shader

#version 410 core


//Input
in vec3 InPosition;

//Output


void main()
{
    gl_Position = vec4(InPosition, 1.0);
}