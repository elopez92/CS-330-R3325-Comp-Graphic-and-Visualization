#version 440 core

layout(location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // add transformation to vertices
}