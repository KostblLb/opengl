#version 430 
in vec4 vPosition;
in vec4 vColor;
uniform mat4 scale_m;

out vec4 fColor;

void main(){
gl_Position = scale_m*vPosition;
fColor = vColor;
}