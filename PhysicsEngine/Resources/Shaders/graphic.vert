#version 330 core
/*
    Input: [vec4] texture information
    Output: [vec2] position and [vec2] texture coords
*/

// (position [vec2], texCoord [vec2])
layout (location = 0) in vec4 vertex;
out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
    // Apply transformation to coordinates
    gl_Position = projection * view * model * vec4(vertex.xy, 0, 1);
    texCoord = vertex.zw;
}

