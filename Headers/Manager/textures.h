#pragma once
#ifndef MANAGER_TEXTURES_H
#define MANAGER_TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>

class Game;

class Textures
{
public:
	Textures();
	~Textures();

	void init(Game *game);

	// if it's already stored, just hand back the existing one
	SDL_Texture **store(const std::string &filePath);

	// doesn't store new texture if doesnt exist
	inline SDL_Texture **get(const std::string &filePath)
	{
		try
		{
			return &this->_textures.at(filePath);
		}
		catch (std::exception err)
		{
			throw err.what();
			return nullptr;
		}
	}

protected:


private:
	Game *_game;

	std::unordered_map<std::string, SDL_Texture *> _textures;
};

#endif