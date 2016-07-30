#include <Game/game.h>
#include <iostream>

Game::Game()
{
	std::cout << "Constructor called on Game!\n";

	this->input.init(this);
	this->window.init(this);

	// A calm electronic synth fades into being, and in the distance; you hear a group of individuals singing "ha--ha-ha-ha---ha"... so true; funny how it seems - always in time, but never inline for dreams.
	while(true)
	{
		this->tick();
	}
}

Game::~Game()
{

}

void Game::tick()
{
	this->input.tick();
	this->window.tick();

}
