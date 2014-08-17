#include "App.h"
#include "LoadShaders.h"
#include <exception>
#include <string>
#include <iostream>


App* App::a = NULL;
SDL_Window* window;
GLuint program;
GLint currentFrame = 0;

int App::Init(Uint32 WindowFlags, int samples){
	try{
		if (SDL_Init(SDL_INIT_VIDEO)) {
			throw SDL_GetError();
		}
	}
	catch (const char* msg){
		std::cerr << "Error initialising SDL:\n" << msg << std::endl;
		running = 0;
		return -1;
	}
	if (samples > 1){
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);
	}

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	window = SDL_CreateWindow("Hello!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, WindowFlags);
	SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		running = 0;
		return -1;
	}

	/*glEnable(), settings block*/
	glEnable(GL_PRIMITIVE_RESTART);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_SAMPLE_COVERAGE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glCullFace(GL_FRONT);
	glPrimitiveRestartIndex(0xF);
	glSampleCoverage(1.0, GL_FALSE);
	SDL_GL_SetSwapInterval(1);

	ShaderInfo shaders[] =
	{ { GL_VERTEX_SHADER, "vshader.vert" },
	{ GL_FRAGMENT_SHADER, "fshader.frag" },
	{ GL_NONE, NULL } };
	program = LoadShaders(shaders);
	glUseProgram(program);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearStencil(0x1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void App::Events(){
	SDL_Event event;
	if (!SDL_PollEvent(&event)) return;
	if (event.type == SDL_QUIT){
		running = 0;
	}
}

void App::Update(){
	currentFrame++;
	return;
}

void App::Cleanup(){
	while (SDL_GL_GetCurrentWindow() != NULL){
		while (SDL_GL_GetCurrentContext() != NULL)
			SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
		SDL_DestroyWindow((SDL_Window*)SDL_GL_GetCurrentWindow());
	}
	SDL_Quit();
}

void App::Render(){
	GLfloat stencil[] = {
		-0.2, -0.2, 0.2, 1.0,
		-0.2, 0.2, 0.2, 1.0,
		0.2, 0.2, 0.2, 1.0,
		0.2, -0.2, 0.2, 1.0,
	};
	GLushort stencil_indices[] = {
		0,3,2,1,0
	};
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
	{ 1.0, 1.0, 1.0, sinf(GLfloat(currentFrame)/120.0),
	0.0, 1.0, 1.0, cosf(GLfloat(currentFrame)/120.0),
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
	GLfloat rotX[] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, cosf(180.0 / M_PI*45.0), -sinf(180.0 / M_PI*45.0), 0.0,
		0.0, sinf(180.0 / M_PI*45.0), cosf(180.0 / M_PI*45.0), 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	GLfloat rotZ[] = {
		cosf(GLfloat(currentFrame) / 60.0), -sinf(GLfloat(currentFrame) / 60.0), 0.0, 0.0,
		sinf(GLfloat(currentFrame) / 60.0), cosf(GLfloat(currentFrame) / 60.0), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	GLuint buffers[3];
	GLuint vao[2];
	glClearStencil(0x0);
	glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);	
	GLint rotX_loc = glGetUniformLocation(program, "rotX");
	GLint rotZ_loc = glGetUniformLocation(program, "rotZ");
	glUniformMatrix4fv(rotX_loc, 1, GL_FALSE, rotX);
	glUniformMatrix4fv(rotZ_loc, 1, GL_FALSE, rotZ);
	glGenBuffers(3, buffers);
	glGenVertexArrays(2, vao);

	/*plane*/
	glStencilFunc(GL_NEVER, 0x1, 0xF);
	glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
	glStencilMask(0xF);
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stencil), stencil, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stencil_indices), stencil_indices, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_SHORT, NULL);

	/*cube*/
	glStencilFunc(GL_EQUAL, 0x1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(vert_colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vert_colors), vert_colors);
	glBindVertexArray(vao[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(vertices));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);

	SDL_GL_SwapWindow(window);

}

App* App::Instance(){
	if (!a)
		a = new App;
	return a;
}