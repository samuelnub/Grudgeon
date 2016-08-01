#pragma once
#ifndef HANDLER_INPUT_H
#define HANDLER_INPUT_H

#include <SDL2/SDL.h>
#include <vector>
#include <array>

class Game;

class Input
{
public:
	Input();
	~Input();

	void init(Game *game);

	void tick();

	inline float getDelta()
	{
		return this->_deltaTime;
	}
	// Returns the total time the program's been open up till the start of the current frame
	inline float getTotalTime()
	{
		return this->_totalTime;
	}

	inline bool wasKeyPressed(int key)
	{
		return this->_pressedKeys[key];
	}

	inline bool wasKeyReleased(int key)
	{
		return this->_releasedKeys[key];
	}

	inline bool isKeyHeld(int key)
	{
		return this->_heldKeys[key];
	}

	inline bool wasMouseButtonPressed(int button)
	{
		return this->_pressedMouseButtons[button];
	}

	inline bool wasMouseButtonReleased(int button)
	{
		return this->_releasedMouseButtons[button];
	}

	inline int getCursorX()
	{
		return this->_cursorX;
	}

	inline int getCursorY()
	{
		return this->_cursorY;
	}

	inline int getCursorMovedX()
	{
		return this->_cursorMovedX;
	}

	inline int getCursorMovedY()
	{
		return this->_cursorMovedY;
	}

	inline int getScrollX()
	{
		return this->_scrolledX;
	}

	inline int getScrollY()
	{
		return this->_scrolledY;
	}

	inline bool isWindowInFocus()
	{
		return this->_windowInFocus;
	}

	inline bool didWindowSizeChange()
	{
		return this->_windowSizeChanged;
	}

	inline bool didWindowMove()
	{
		return this->_windowMoved;
	}

protected:


private:
	Game *_game;

	SDL_Event _event;

	std::vector<SDL_Event> _frameEvents;

	std::array<bool, 1024> _heldKeys;
	std::array<bool, 1024> _pressedKeys;
	std::array<bool, 1024> _releasedKeys;

	std::array<bool, 5> _pressedMouseButtons;
	std::array<bool, 5> _releasedMouseButtons;

	int _cursorX;
	int _cursorY;
	int _cursorMovedX;
	int _cursorMovedY;

	int _scrolledX;
	int _scrolledY;

	bool _windowInFocus;
	bool _windowSizeChanged;
	bool _windowMoved;

	float _deltaTime;
	float _lastFrameTime;
	float _totalTime;

	void process();

	void keyDownEvent(size_t &index);
	void keyHeldEvent(size_t &index);
	void keyUpEvent(size_t &index);
	void mouseMotionEvent(size_t &index);
	void mouseScrollEvent(size_t &index);
	void mouseButtonDownEvent(size_t &index);
	void mouseButtonUpEvent(size_t &index);

	void windowFocusGainEvent(size_t &index);
	void windowFocusLossEvent(size_t &index);
	void windowSizeChangeEvent(size_t &index);
	void windowMoveEvent(size_t &index);
};

#endif