#include <Handler/window.h>
#include <Game/game.h>
#include <iostream>
#include <algorithm>

Window::Window()
{
}

Window::~Window()
{
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
	std::cout << "Destructor called on Window!\n";
}

void Window::init(Game *game)
{
	this->_game = game;
	
	this->_displayIndex = this->_game->settings.getInt("WindowDisplayNum");

	this->_windowFlags = 0;
	// bitwise operators are like a really good pizza - it feels good to smudge on yourself, uh, what?
	if (this->_game->settings.getBool("WindowFullscreen"))
	{
		this->_windowFlags = this->_windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (this->_game->settings.getBool("WindowBorderless"))
	{
		this->_windowFlags = this->_windowFlags | SDL_WINDOW_BORDERLESS;
	}
	if (this->_game->settings.getBool("WindowResizable"))
	{
		this->_windowFlags = this->_windowFlags | SDL_WINDOW_RESIZABLE;
	}

	if (SDL_CreateWindowAndRenderer(this->_game->settings.getInt("WindowWidth"), this->_game->settings.getInt("WindowHeight"), this->_windowFlags
		, &this->_window, &this->_renderer) != 0)
	{
		throw "Error! Couldn't create window!\n";
	}
	else
	{
		std::cout << "Successfully initialized Window!\n";
	}
	SDL_SetWindowTitle(this->_window, this->_game->settings.getString("ProgramName").c_str());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); //TODO: 0 is nearest filtering, so it looks like a cheaply made indie game
	
	this->handle();
}

void Window::tick()
{
	if (this->_game->input.didWindowMove() ||
		this->_game->input.didWindowSizeChange())
	{
		this->handle();
	}
}

void Window::handle()
{
	this->_displayIndex = SDL_GetWindowDisplayIndex(this->_window);

	SDL_GetCurrentDisplayMode(this->_displayIndex, &this->_displayMode);

	SDL_GetWindowSize(this->_window, &this->_windowMode.w, &this->_windowMode.h);

	SDL_GetWindowPosition(this->_window, &this->_windowMode.x, &this->_windowMode.y);

	this->scaleRenderer();

	std::cout << "The window was updated in some form!\n" <<
		"It's currently sitting on the display with an index of " << this->_displayIndex << "\n" <<
		"A screen width and height of " << this->_displayMode.w << " and " << this->_displayMode.h << "\n" <<
		"And a refresh rate of " << this->_displayMode.refresh_rate << "\n" <<
		"Oh, and now the window itself has the dimensions of " << this->_windowMode.w << " by " << this->_windowMode.h << "\n" <<
		"At the position " << this->_windowMode.x << " and " << this->_windowMode.y << "\n";
}

void Window::scaleRenderer()
{
	if (this->_windowMode.w <= 0)
	{
		SDL_SetWindowSize(this->_window, 1, this->_windowMode.h);
	}
	if (this->_windowMode.h <= 0)
	{
		SDL_SetWindowSize(this->_window, this->_windowMode.w, 1);
	}


	SDL_RenderSetLogicalSize(this->_renderer,
		this->_game->settings.getInt("RenderWidth"),
		this->_game->settings.getInt("RenderHeight"));

	// scale the renderer to the smallest window w/h, and to fill up the remaining empty space (assuming the aspect ratio wasn't conserved), increase the rendering resolution of that axis till it fits
	// so the minimum scaled side retains its rendering resolution from settings.xml, but the other side increases its resolution to fit the window
	
	int curWindW;
	int curWindH;

	SDL_GetWindowSize(this->_window, &curWindW, &curWindH);
	
	int tempWinDMin = std::min(curWindW, curWindH);

	int curRendW;
	int curRendH;

	SDL_RenderGetLogicalSize(this->_renderer, &curRendW, &curRendH);

	int tempRendMin = std::min(curRendW, curRendH);

	float aspectMin = static_cast<float>(tempWinDMin) / tempRendMin; // scale on both x and y

	float tempWindMax = std::max(curWindW, curWindH);
	//TODO: possible floating point inaccuracies
	curRendW = (static_cast<int>(curRendW * aspectMin) == tempWinDMin) ? curRendW : tempWindMax / aspectMin;
	curRendW = (static_cast<int>(curRendH * aspectMin) == tempWinDMin) ? curRendH : tempWindMax / aspectMin;

	SDL_RenderSetLogicalSize(this->_renderer, curRendW, curRendH);

	// set scale to be uniform on x and y
	SDL_RenderSetScale(this->_renderer, aspectMin, aspectMin);

	//it's scaled up and we want the min renderer side to remain the same, as it's currently already fitted nicely, but the other side? theres now a blank space, lets increase the rendering resolution of the renderer on that axis

	SDL_RenderGetLogicalSize(this->_renderer, &this->_renderMode.w, &this->_renderMode.h);
	SDL_RenderGetScale(this->_renderer, &this->_renderMode.scaleX, &this->_renderMode.scaleY);
}
