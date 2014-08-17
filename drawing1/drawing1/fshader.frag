#version 430 
sample in vec4 fColor;
out vec4 color;

void main(){

	color = vec4(fColor.r, fColor.g, fColor.b, 1.0);
	}