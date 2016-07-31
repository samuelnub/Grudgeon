#pragma once
#ifndef MANAGER_TEXTURES_H
#define MANAGER_TEXTURES_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <iostream>

class Game;

// This class just manages textures, their source and dest rects are specified per-actor
class Textures
{
public:
	Textures();
	~Textures();

	void init(Game *game);

	// Give it the filepath, itll grab it, create a texture from it, store it here, and hand you back a pointer to it (or a pointer to pointer, since these ol' sdl_textures are kept as pointers)
	SDL_Texture **store(std::string filePath, int alphaAmount = 255);

	// Name will most likely be filepath, as that's how you'd most likely store it
	inline SDL_Texture **get(std::string name)
	{
		try
		{
			return &this->_textures.at(name);
		}
		catch (std::exception err)
		{
			std::cout << "Couldn't get texture with the name " << name << ", most likely never loaded - here's the error: " << err.what() << "\n"; // lol "err, what"
			return nullptr;
		}
	}

protected:


private:
	Game *_game;

	std::unordered_map<std::string, SDL_Texture *> _textures;

};

#endif