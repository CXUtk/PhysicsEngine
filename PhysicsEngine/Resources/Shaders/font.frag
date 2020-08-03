#version 330 core
/*
    Input: [vec2] texture coords from vertex shader
    Output: [vec4] color of text render by textColor
*/

in vec2 texCoord;
out vec4 color;

uniform sampler2D texChar;
uniform vec3 textColor;

void main(){
    vec4 sampled = vec4(1, 1, 1, texture2D(texChar, texCoord).r);
    color = vec4(textColor, 1) * sampled;
}