#pragma once
#ifndef HANDLER_WINDOW_H
#define HANDLER_WINDOW_H

#include <SDL2/SDL.h>

class Game;

struct WindowMode
{
	int w;
	int h;

	int x; // Position of window
	int y;

	WindowMode()
	{
		this->w = 420; // heh
		this->h = 380; 
		this->x = 100;
		this->y = 100;
	}

	WindowMode(int newW, int newH)
	{
		this->w = newW;
		this->h = newH;
	}

	WindowMode(int newW, int newH, int newX, int newY)
	{
		this->w = newW;
		this->h = newH;
		this->x = newX;
		this->y = newY;
	}
};

struct RenderMode
{
	int w; // renderer logical size
	int h;

	float scaleX; // up/downscale to fit the windowmode
	float scaleY;

	RenderMode()
	{
		this->w = 210;
		this->h = 190;
	}

	RenderMode(int newW, int newH)
	{
		this->w = newW;
		this->h = newH;
	}
};

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

	// Display mode is your physical monitor's stats, not the info of your current lil' window

	// Returns pointer to pointer, joy to the world...
	inline SDL_Renderer **getRenderer()
	{
		return &this->_renderer;
	}

	inline const SDL_DisplayMode *getDisplayMode()
	{
		return &this->_displayMode;
	}

	inline const WindowMode *getWindowMode()
	{
		return &this->_windowMode;
	}

	inline const RenderMode *getRenderMode()
	{
		return &this->_renderMode;
	}

protected:


private:
	Game *_game;

	SDL_Window *_window;

	int _windowFlags;

	SDL_Renderer *_renderer;

	int _displayIndex;

	SDL_DisplayMode _displayMode;

	WindowMode _windowMode;

	RenderMode _renderMode;

	// Gets called on init and when tick'd if window's been resized etc...
	void handle();
	void scaleRenderer();
};

#endif