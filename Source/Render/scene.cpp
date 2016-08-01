#include <Render/scene.h>
#include <Game/game.h>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::init(Game * game)
{
	this->_game = game;

}

void Scene::draw()
{

	SDL_RenderPresent(*this->_game->window.getRenderer());
}
