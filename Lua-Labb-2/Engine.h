#pragma once
#include "LuaState.h"

class Engine
{
public:
	Engine();
	~Engine();
	void run();
private:
	LuaState luaState;

	bool isRunning;
	char board[9];

	void update();
	void draw();
};

