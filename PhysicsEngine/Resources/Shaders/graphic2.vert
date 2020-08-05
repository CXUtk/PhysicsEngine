#version 330 core
/*
    Input: [vec3] position of the vertex
    Output: [null]
*/

layout (location = 0) in vec2 aPos;

uniform mat4 projection;

void main(){
    // Apply transformation to coordinates
    gl_Position = projection * vec4(aPos, 0, 1);
}

