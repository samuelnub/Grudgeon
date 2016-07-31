#include <Manager/textures.h>
#include <SDL2/SDL_image.h>
#include <Game/game.h>

Textures::Textures()
{
}

Textures::~Textures()
{
}

void Textures::init(Game * game)
{
	this->_game = game;
}

SDL_Texture **Textures::store(std::string filePath, int alphaAmount)
{
	this->_textures[filePath] = IMG_LoadTexture(*this->_game->window.getRenderer(), filePath.c_str());



	return this->get(filePath);
}