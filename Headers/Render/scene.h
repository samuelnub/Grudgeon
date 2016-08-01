#pragma once
#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include <SDL2/SDL.h>

class Game;

class Scene
{
public:
	Scene();
	~Scene();

	void init(Game *game);

	void tick();

protected:


private:
	Game *_game;

};

#endif