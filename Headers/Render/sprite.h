#pragma once
#ifndef RENDER_SPRITE_H
#define RENDER_SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Game;

// Animation struct for textures, if x and y is 1, its a still frame, aka a non-animated sprite, animations go left to right, then top to bottom, x gets looped, then y increments, etc...
struct Animation
{
	int xFrames;
	int yFrames;
	
	float timeToUpdate;

	Animation() // default constructor assumes its not animated
	{
		this->xFrames = 1;
		this->yFrames = 1;

		this->timeToUpdate = 
	}
};

// Sprite component for your actors
// 
class Sprite
{
public:
	Sprite();
	~Sprite();

	// Will be stored in texture manager's map as the filepath for the key
	void init(Game *game, std::string filePath, );

	void tick();

private:


protected:
	Game *_game;

	SDL_Texture *_texture;
	SDL_Rect _sourceRect;
	SDL_Rect _destRect;

	double _angle;
	SDL_Point _origin; // i prefer steam
	int _flipFlag; // its an enum
};

#endif