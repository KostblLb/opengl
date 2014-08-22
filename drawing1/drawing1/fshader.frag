#version 400 
in vec4 fColor;
out vec4 color;

void main(void){

	color = vec4(fColor.r, fColor.g, fColor.b, fColor.a);
	}