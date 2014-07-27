#include <iostream>
#include <SDL.h>
#include <glew.h>
using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Hello!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);

	SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	GLuint vbuffer;
	GLuint ebuffer;
	GLfloat vertices[] =
	{ -0.5, -0.5, 0.0, 1.0,
	-0.5, 0.5, 0.0, 1.0,
	0.5, -0.5, 0.0, 1.0 };
	GLfloat vert_colors[] =
	{ 0.0, 1.0, 1.0, 1.0,
	1.0, 0.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0 };
	GLushort indices[] = { 0, 1, 2 };
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &ebuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(vert_colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vert_colors), vert_colors);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint vaos[1];
	GLuint vap;
	glGenVertexArrays(1, vaos);
	glBindVertexArray(vaos[0]);
	glVertexAttribPointer(vap, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vap);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
	SDL_GL_SwapWindow(window);
	SDL_Delay(1000);
	SDL_Quit();
	return 0;
}

