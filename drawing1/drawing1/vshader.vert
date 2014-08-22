#version 400 
layout (location = 0)in vec4 vPosition;
layout (location = 1)in vec4 vColor;
uniform mat4 rotX;
uniform mat4 rotZ;
out vec4 fColor;
void main(void){
    gl_Position = rotX*rotZ*vPosition;
    fColor = vColor;
}
