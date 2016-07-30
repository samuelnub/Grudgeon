#pragma once
#ifndef HANDLER_WINDOW_H
#define HANDLER_WINDOW_H

#include <SDL2/SDL.h>

class Game;



class Window
{
public:
	Window();
	
	// Destructor deletes this window and renderer
	~Window();

	// Create SDL context window
	void init(Game *game);

	// Checks for resizes, and checks for framerate changes when switching displays
	void tick();

	inline const SDL_DisplayMode *getDisplayMode()
	{
		return this->_displayMode;
	}

protected:


private:
	Game *_game;

	SDL_Window *_window;

	SDL_Renderer *_renderer;

	int _displayIndex;

	SDL_DisplayMode *_displayMode;

};

#endif