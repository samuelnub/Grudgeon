#include <Render/renderable.h>
#include <Game/game.h>
#include <iostream>
#include <boost/math/special_functions/round.hpp>

Renderable::Renderable()
{
}

Renderable::~Renderable()
{
}

void Renderable::init(Game * game, const std::string &filePath, Vec2<int> sourceXY, Vec2<int> sourceWH, Vec2<int> destXY, Vec2<int> destWH, Vec2<float> scale, float angle, Vec2<int> origin, bool visible)
{
	this->_game = game;

	this->_texture = IMG_LoadTexture(*this->_game->window.getRenderer(), filePath.c_str());
	if (this->_texture == nullptr)
	{
		std::cout << "Couldn't load texture with the file path of " << filePath << "!\n" << SDL_GetError() << "\n";
	}

	this->_sourceRect.x = destXY.x;
	this->_sourceRect.y = destXY.y;
	this->_sourceRect.w = destWH.x;
	this->_sourceRect.h = destWH.y;

	this->_destRect.x = destXY.x;
	this->_destRect.y = destXY.y;
	this->_destRect.w = destWH.x;
	this->_destRect.h = destWH.y;

	this->_scale = scale;
	this->_angle = angle;
	
	this->_origin.x = origin.x;
	this->_origin.y = origin.y;
	this->scale(this->_scale);
	this->rotate(this->_angle);

	this->_flipFlag = SDL_FLIP_NONE;

	this->_isAnimated = false;
	this->_curAnimRepeat = true;
	this->_curFrameIndex = Vec2<int>();

	this->_visible = visible;
}

void Renderable::init(Game * game, const std::string &filePath, SDL_Rect sourceRect, SDL_Rect destRect, Vec2<float> scale, float angle, SDL_Point origin, bool visible)
{
	this->_game = game;

	this->_texture = IMG_LoadTexture(*this->_game->window.getRenderer(), filePath.c_str());
	if (this->_texture == nullptr)
	{
		std::cout << "Couldn't load texture with the file path of " << filePath << "!\n" << SDL_GetError() << "\n";
	}

	this->_sourceRect = sourceRect;
	this->_destRect = destRect;

	this->_scale = scale;
	this->_angle = angle;

	this->_origin = origin;
	this->scale(this->_scale);
	this->rotate(this->_angle);

	this->_flipFlag = SDL_FLIP_NONE;

	this->_isAnimated = false;
	this->_curAnimRepeat = true;
	this->_curFrameIndex = Vec2<int>();

	this->_visible = visible;
}

void Renderable::tick()
{
	if (this->_isAnimated && this->_isAnimating)
	{
		this->animate();
	}

	//TODO: temp only in renderable.cpp
	if (this->_visible)
	{
		SDL_RenderCopyEx(*this->_game->window.getRenderer(), this->_texture, &this->_sourceRect, &this->_destRect, this->_angle, &this->_origin, this->_flipFlag);
	}
}

void Renderable::translate(int x, int y)
{
	this->_destRect.x += x;
	this->_destRect.y += y;
}

void Renderable::translate(Vec2<int> xy)
{
	this->_destRect.x += xy.x;
	this->_destRect.y += xy.y;
}

void Renderable::scale(float xFactor, float yFactor, bool keepCentred)
{
	this->_scale.x = xFactor;
	this->_scale.y = yFactor;

	if (keepCentred)
	{
		this->translate(Vec2<int>(
			boost::math::iround<>(this->_destRect.w / xFactor),
			boost::math::iround<>(this->_destRect.h / yFactor)
			));
	}

	this->_destRect.w *= this->_scale.x;
	this->_destRect.h *= this->_scale.y;
}

void Renderable::scale(Vec2<float> factors, bool keepCentred)
{
	this->_scale = factors;

	if (keepCentred)
	{
		this->translate(Vec2<int>(
			boost::math::iround<>(this->_destRect.w / factors.x),
			boost::math::iround<>(this->_destRect.h / factors.y)
			));
	}

	this->_destRect.w *= this->_scale.x;
	this->_destRect.h *= this->_scale.y;
}

void Renderable::rotate(float angle, Vec2<float> origin)
{
	this->_angle += angle;

	this->_origin.x = origin.x;
	this->_origin.y = origin.y;
}

void Renderable::rotate(float angle, SDL_Point origin)
{
	this->_angle += angle;
	
	this->_origin = origin;
}

void Renderable::rotate(float angle)
{
	this->_angle += angle;
}

void Renderable::flip(SDL_RendererFlip flip)
{
	this->_flipFlag = flip;
}

void Renderable::animate()
{
	this->_timeElapsed += this->_game->input.getDelta();

	this->_isAnimating = true;

	if (this->_timeElapsed > this->_animations.at(this->_currentAnim).updateTime)
	{
		this->_timeElapsed -= this->_animations.at(this->_currentAnim).updateTime;
		if (this->_curFrameIndex.x < this->_animations.at(this->_currentAnim).xyFrameCount.x)
		{
			this->_curFrameIndex.x++;
			std::cout << "Incrementing frame index x\n";
		}
		else if (this->_curFrameIndex.x >= this->_animations.at(this->_currentAnim).xyFrameCount.x &&
			this->_curFrameIndex.y < this->_animations.at(this->_currentAnim).xyFrameCount.y)
		{
			this->_curFrameIndex.x = 0;
			this->_curFrameIndex.y++;
			std::cout << "Incrementing frame index y and resetting x to 0\n";
		}
		else if (this->_curFrameIndex.x >= this->_animations.at(this->_currentAnim).xyFrameCount.x &&
			this->_curFrameIndex.y >= this->_animations.at(this->_currentAnim).xyFrameCount.y &&
			this->_curAnimRepeat == true)
		{
			this->_curFrameIndex = Vec2<int>();
			std::cout << "Finished a cycle of animation, repeating!\n";
		}
		else if(this->_curFrameIndex.x >= this->_animations.at(this->_currentAnim).xyFrameCount.x &&
			this->_curFrameIndex.y >= this->_animations.at(this->_currentAnim).xyFrameCount.y && 
			this->_curAnimRepeat == false)
		{
			this->_isAnimating = false;
			std::cout << "Stopped animation as repeat was false!\n";
		}
	}

	this->_sourceRect.x = this->_animations.at(this->_currentAnim).initialOffset.x +
		(this->_curFrameIndex.x * this->_sourceRect.w);
	this->_sourceRect.y = this->_animations.at(this->_currentAnim).initialOffset.y +
		(this->_curFrameIndex.y * this->_sourceRect.h);
}

void Renderable::storeAnim(const std::string &name, Animation anim)
{
	this->_isAnimated = true;
	this->_isAnimating = true;
	this->_animations[name] = anim;
}

void Renderable::useAnim(const std::string &name, bool repeat)
{
	this->_currentAnim = name;

	this->_curAnimRepeat = repeat;
}
