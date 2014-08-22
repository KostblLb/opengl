
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <SDL.h>
#include <glew.h>
#include "App.h"
#include "LoadShaders.h"

using namespace std;


int main(int argc, char* argv[])
{
	std::streambuf* pbuf;
	std::fstream log;
	log.open("debug.txt", std::fstream::out);
	pbuf = log.rdbuf();
	std::cerr.rdbuf(pbuf);
	//std::cout.rdbuf(pbuf);
	if(App::Instance()->Init(SDL_WINDOW_OPENGL, 8) == -1)
		return 1;
	while (App::Instance()->isRunning()){
		App::Instance()->Events();
		App::Instance()->Update();
		App::Instance()->Render();
	}
	App::Instance()->Cleanup();
	return 0;
}

