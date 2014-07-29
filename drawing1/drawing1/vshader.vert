#version 430 
in vec4 vPosition;
in vec4 vColor;
uniform mat4 scale_m;
uniform mat4 rotZ;
uniform mat4 rotX;

out vec4 fColor;

void main(){
gl_Position = rotX*rotZ*scale_m*vPosition;
fColor = vColor;
}