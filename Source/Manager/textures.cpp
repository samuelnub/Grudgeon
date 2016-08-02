#include <Manager/textures.h>
#include <Game/game.h>

Textures::Textures()
{
}

Textures::~Textures()
{
}

void Textures::init(Game *game)
{
	this->_game = game;

}

SDL_Texture **Textures::store(const std::string &filePath)
{
	if (this->get(filePath) != nullptr)
	{
		return this->get(filePath);
	}

	this->_textures[filePath] = IMG_LoadTexture(*this->_game->window.getRenderer(), filePath.c_str());
	if (this->_textures[filePath] == nullptr)
	{
		std::cout << "Couldn't load texture with the file path of " << filePath << "!\n" << SDL_GetError() << "\n";
		return nullptr;
	}
	
	return this->get(filePath);
}