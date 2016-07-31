#pragma once
#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

class Game;

class Scene
{
public:
	Scene();
	~Scene();

	void init(Game *game);


	void draw();

protected:


private:
	Game *_game;

};

#endif