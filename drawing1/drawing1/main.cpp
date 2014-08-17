
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <glew.h>
#include "App.h"
#include "LoadShaders.h"

using namespace std;


int main(int argc, char* argv[])
{
	if(App::Instance()->Init(SDL_WINDOW_OPENGL, 4) == -1)
		return 1;
	while (App::Instance()->isRunning()){
		App::Instance()->Events();
		App::Instance()->Update();
		App::Instance()->Render();
	}
	App::Instance()->Cleanup();
	
/*	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	SDL_Window* window = SDL_CreateWindow("Hello!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);

	SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
	SDL_Quit();
	exit(EXIT_FAILURE);
	}
	glEnable(GL_PRIMITIVE_RESTART);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_COVERAGE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glSampleCoverage(1.0, GL_FALSE);
	glCullFace(GL_FRONT);
	glPrimitiveRestartIndex(0xF);

	GLint w, h;
	SDL_GetWindowSize(window, &w, &h);
	GLfloat aspect = GLfloat(w) / GLfloat(h);
	GLfloat scale[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, aspect, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
	};
	GLfloat rotX[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, cosf(180.0 / M_PI*45.0), -sinf(180.0 / M_PI*45.0), 0.0,
	0.0, sinf(180.0 / M_PI*45.0), cosf(180.0 / M_PI*45.0), 0.0,
	0.0, 0.0, 0.0, 1.0
	};
	GLfloat rotZ[] = {
	cosf(180.0 / M_PI*45.0), -sinf(180.0 / M_PI*45.0), 0.0, 0.0,
	sinf(180.0 / M_PI*45.0), cosf(180.0 / M_PI*45.0), 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
	};

	GLuint vbuffer;
	GLuint ebuffer;
	GLfloat vertices[] =
	{ -0.5, -0.5, -0.5, 1.0,
	-0.5, -0.5, 0.5, 1.0,
	-0.5, 0.5, -0.5, 1.0,
	-0.5, 0.5, 0.5, 1.0,
	0.5, -0.5, -0.5, 1.0,
	0.5, -0.5, 0.5, 1.0,
	0.5, 0.5, -0.5, 1.0,
	0.5, 0.5, 0.5, 1.0
	};
	GLfloat vert_colors[] =
	{ 1.0, 1.0, 1.0, 1.0,
	0.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.5, 0.5, 0.5, 1.0, };


	static const GLushort indices[] = {
	0, 1, 2, 3, 6, 7, 4, 5,
	0xF,
	2, 6, 0, 4, 1, 5, 3, 7
	};

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
	glGenVertexArrays(1, vaos);
	glBindVertexArray(vaos[0]);

	GLuint program;
	ShaderInfo shaders[] =
	{ { GL_VERTEX_SHADER, "vshader.vert" },
	{ GL_FRAGMENT_SHADER, "fshader.frag" },
	{ GL_NONE, NULL } };
	program = LoadShaders(shaders);
	glUseProgram(program);

	GLint SampleBuffers, SamplesPerPixel;
	GLfloat SampleCoords[2];
	glGetIntegerv(GL_SAMPLE_BUFFERS, &SampleBuffers);
	glGetIntegerv(GL_SAMPLES, &SamplesPerPixel);
	if (SampleBuffers)
	glGetMultisamplefv(GL_SAMPLE_POSITION, 0, SampleCoords);
	GLint posIndex = glGetAttribLocation(program, "vPosition");
	GLint colIndex = glGetAttribLocation(program, "vColor");
	GLint scalemIndex = glGetUniformLocation(program, "scale_m");
	GLint rotX_loc = glGetUniformLocation(program, "rotX");
	GLint rotZ_loc = glGetUniformLocation(program, "rotZ");
	glUniformMatrix4fv(scalemIndex, 1, GL_FALSE, scale);
	glUniformMatrix4fv(rotX_loc, 1, GL_FALSE, rotX);
	glUniformMatrix4fv(rotZ_loc, 1, GL_FALSE, rotZ);
	glVertexAttribPointer(posIndex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(colIndex, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*) sizeof(vertices));
	glEnableVertexAttribArray(posIndex);
	glEnableVertexAttribArray(colIndex);

	glClear(GL_COLOR_BUFFER_BIT);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
	//glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 0);
	//glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_SHORT, NULL);

	SDL_GL_SwapWindow(window);
	while (1){
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT){
	glDeleteBuffers(1, &ebuffer);
	glDeleteBuffers(1, &vbuffer);
	glDeleteProgram(program);
	glFlush();
	SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
	SDL_DestroyWindow(window);
	SDL_Quit();
	break;
	}
	}*/

	return 0;
}

