#include <Handler/window.h>
#include <Game/game.h>
#include <iostream>

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

	std::cout << "The window was updated in some form!\n" <<
		"It's currently sitting on the display with an index of " << this->_displayIndex << "\n" <<
		"A screen width and height of " << this->_displayMode.w << " and " << this->_displayMode.h << "\n" <<
		"And a refresh rate of " << this->_displayMode.refresh_rate << "\n" <<
		"Oh, and now the window itself has the dimensions of " << this->_windowMode.w << " by " << this->_windowMode.h << "\n" <<
		"At the position " << this->_windowMode.x << " and " << this->_windowMode.y << "\n";
}
