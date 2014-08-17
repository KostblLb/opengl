#include <stdio.h>
#include <SDL.h>
#include <glew.h>
#include "LoadShaders.h"

class App{
public:
	int Init(Uint32 flags, int samples);
	void Events();
	void Update();
	void Render();
	void Cleanup();
	static App* Instance();
	int isRunning(){ return running; }
private:
	int running;
	static App* a;
	App() :running(1){};
	~App();
};

