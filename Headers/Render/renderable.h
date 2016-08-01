#pragma once
#ifndef RENDER_SPRITE_H
#define RENDER_SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

class Game;

template <typename T>
struct Vec2
{
	T x;
	T y;

	Vec2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vec2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
};

// Animation struct for textures, if x and y is 1, its a still frame, aka a non-animated sprite, animations go left to right, then top to bottom, x gets looped, then y increments, etc...
struct Animation
{
	Vec2<int> xyFrameCount;
	Vec2<int> initialOffset; // animation sheets would most likely be stacked downward, toward +y, so x should most likely be 0 in all cases.
	
	int updateTime; // in ms

	Animation() // default constructor assumes its not animated
	{
		this->xyFrameCount = Vec2<int>();
		this->initialOffset = Vec2<int>();
		this->updateTime = 60;
	}

	Animation(Vec2<int> xyCount, Vec2<int> offset, int time)
	{
		this->xyFrameCount = xyCount;
		this->initialOffset = offset;
		this->updateTime = time;
	}
};

// Sprite/tile/whatever textured component for your actor
class Renderable
{
public:
	Renderable();
	~Renderable();
	
	void init(Game *game, const std::string &filePath, Vec2<int> sourceXY, Vec2<int> sourceWH, Vec2<int> destXY, Vec2<int> destWH, Vec2<float> scale = Vec2<float>(1.0f,1.0f), float angle = 0, Vec2<int> origin = Vec2<int>(), bool visible = true);

	void init(Game *game, const std::string &filePath, SDL_Rect sourceRect, SDL_Rect destRect, Vec2<float> scale = Vec2<float>(1.0f, 1.0f), float angle = 0, SDL_Point origin = SDL_Point(), bool visible = true);

	inline SDL_Texture **getTexture()
	{
		return &this->_texture;
	}
	
	// Mostly redundant, for manual setting
	inline void setSourceRect(SDL_Rect rect)
	{
		this->_sourceRect = rect;
	}

	inline SDL_Rect getSourceRect()
	{
		return this->_sourceRect;
	}

	// Mostly redundant, for manual setting. You'd most likely want to use those transform functions below
	inline void setDestRect(SDL_Rect rect)
	{
		this->_destRect = rect;
	}

	inline SDL_Rect getDestRect()
	{
		return this->_destRect;
	}

	// utilised elapsed time from input to animate
	void tick();

	// additive translation
	void translate(int x, int y);
	void translate(Vec2<int> xy);

	// scale around origin
	void scale(float xFactor, float yFactor, bool keepCentred = true);
	void scale(Vec2<float> factors, bool keepCentred = true);

	// additive rotation
	void rotate(float angle, Vec2<float> origin);
	void rotate(float angle, SDL_Point origin);
	void rotate(float angle);

	void flip(SDL_RendererFlip flip);

	void storeAnim(const std::string &name, Animation anim);
	void useAnim(const std::string &name, bool repeat = true);

	inline void setAnimating(bool animate)
	{
		this->_isAnimating = animate;
	}

	inline bool isAnimating()
	{
		return this->_isAnimating;
	}

	inline void setVisible(bool vis)
	{
		this->_visible = vis;
	}

	inline bool isVisible()
	{
		return this->_visible;
	}

protected:


private:
	Game *_game;

	SDL_Texture *_texture;
	SDL_Rect _sourceRect;
	SDL_Rect _destRect;

	Vec2<float> _scale;
	double _angle;
	SDL_Point _origin; // i prefer steam
	SDL_RendererFlip _flipFlag; // its an enum
	
	bool _isAnimated; // false on init, assumes its a static renderable
	std::unordered_map<std::string, Animation> _animations;
	std::string _currentAnim; // current animation this instance is set to, each animation is stacked downward, toward +y for SDL
	bool _curAnimRepeat;
	Vec2<int> _curFrameIndex;
	bool _isAnimating;
	int _timeElapsed; // accumulates until the animation's specified time is consumed, then go to next frame

	bool _visible;

	void animate();
};

#endif