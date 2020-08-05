#version 330 core
/*
    Input: [vec2] texture coords from vertex shader
    Output: [vec4] color of text render by textColor
*/
in vec2 texCoord;
out vec4 color;

// Color need to be rendered
uniform vec3 uColor;

void main(){
    const vec2 center = vec2(0.5, 0.5);
    float dis = distance(center, texCoord);
    color = vec4(0);
    if(dis > 0.5) return;
    color = vec4(uColor, 1);
}