#pragma once
#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <Handler/settings.h>
#include <Handler/input.h>
#include <Handler/window.h>

class Game
{
public:
	Game();
	~Game();

	void tick();


	// Public classes for everyone to get stuff from
	Settings settings;
	Input input;
	Window window;

protected:


private:


};

#endif