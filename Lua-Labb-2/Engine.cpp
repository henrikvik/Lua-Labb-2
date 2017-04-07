#include "Engine.h"
#include <iostream>


Engine::Engine()
	: board{ ' ' }
{
}


Engine::~Engine()
{
}

void Engine::run()
{
	luaState.restart();
	luaState.openLibs();
	luaState.doFile("scripts/TicTacToe.lua");

	isRunning = true;
	while (isRunning)
	{
		update();
		draw();
	}
}

void Engine::update()
{
	luaState.get("makeMove");
	luaState.push(1);
	luaState.push("x");
	luaState.call(2);
	system("pause");
}

void Engine::draw()
{
	system("cls");
	std::cout
		<< "-------------" << std::endl
		<< "| " << board[0] << " | " << board[1] << " | " << board[2] << " |" << std::endl
		<< "-------------" << std::endl
		<< "| " << board[3] << " | " << board[4] << " | " << board[5] << " |" << std::endl
		<< "-------------" << std::endl
		<< "| " << board[6] << " | " << board[7] << " | " << board[8] << " |" << std::endl
		<< "-------------" << std::endl;
}
