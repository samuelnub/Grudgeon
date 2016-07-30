#include <Handler/window.h>
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
	//TODO: we got game so we can read off eventual xml file loader for settings

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_CreateWindowAndRenderer(640, 380, NULL, &this->_window, &this->_renderer) != 0)
	{
		throw "Error! Couldn't create window!\n";
	}
	else
	{
		std::cout << "Successfully initialized Window!\n";
	}

	SDL_SetWindowTitle(this->_window, "Grudgeon");
}

void Window::tick()
{
	
}
