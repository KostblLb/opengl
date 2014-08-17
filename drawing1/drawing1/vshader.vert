#version 430 
layout (location = 0)in vec4 vPosition;
layout (location = 1)in vec4 vColor;
layout (location = 2)uniform mat4 rotX;
layout (location = 6)uniform mat4 rotZ;

out vec4 fColor;

void main(){
gl_Position = rotX*rotZ*vPosition;
//gl_Position = vPosition;
fColor = vColor;
}