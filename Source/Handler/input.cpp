#include <Handler/input.h>
#include <Game/game.h>
#include <iostream>

Input::Input()
{
}

Input::~Input()
{
}

void Input::init(Game *game)
{
	this->_game = game;

	std::fill(this->_pressedKeys.begin(), this->_pressedKeys.end(), false);
	std::fill(this->_heldKeys.begin(), this->_heldKeys.end(), false);
	std::fill(this->_releasedKeys.begin(), this->_releasedKeys.end(), false);

	std::fill(this->_pressedMouseButtons.begin(), this->_pressedMouseButtons.end(), false);
	std::fill(this->_releasedMouseButtons.begin(), this->_releasedMouseButtons.end(), false);

	this->_windowInFocus = true;
	this->_windowMoved = false;
	this->_windowSizeChanged = false;

	this->_deltaTime = 0.0f;
	this->_lastFrameTime = 0.0f;

	std::cout << "Successfully initialized the Input!\n";
}

void Input::tick()
{
	this->_totalTime = SDL_GetTicks();
	this->_deltaTime = this->_totalTime - this->_lastFrameTime;
	this->_lastFrameTime = this->_totalTime;

	// Reset key and mouse events each tick, except held keys
	std::fill(this->_pressedKeys.begin(), this->_pressedKeys.end(), false);
	std::fill(this->_releasedKeys.begin(), this->_releasedKeys.end(), false);

	std::fill(this->_pressedMouseButtons.begin(), this->_pressedMouseButtons.end(), false);
	std::fill(this->_releasedMouseButtons.begin(), this->_releasedMouseButtons.end(), false);

	this->_cursorMovedX = 0;
	this->_cursorMovedY = 0;
	
	this->_scrolledX = 0;
	this->_scrolledY = 0;
	
	this->_windowMoved = false;
	this->_windowSizeChanged = false;

	// Multiple events can happen within one frame, handle them
	while (SDL_PollEvent(&this->_event) != 0)
	{
		this->_frameEvents.push_back(this->_event);
	}

	if (!this->_frameEvents.empty())
	{
		this->process();
		this->_frameEvents.clear();
	}
}

void Input::process()
{
	for (size_t i = 0; i < this->_frameEvents.size(); i++)
	{
		switch (this->_frameEvents.at(i).type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(EXIT_SUCCESS);
			break;
		case SDL_KEYDOWN:
			if (this->_frameEvents.at(i).key.repeat == true)
				this->keyHeldEvent(i);
			else if (this->_frameEvents.at(i).key.repeat == false)
				this->keyDownEvent(i);
			break;
		case SDL_KEYUP:
			this->keyUpEvent(i);
			break;
		case SDL_MOUSEMOTION:
			this->mouseMotionEvent(i);
			break;
		case SDL_MOUSEWHEEL:
			this->mouseScrollEvent(i);
			break;
		case SDL_MOUSEBUTTONDOWN:
			this->mouseButtonDownEvent(i);
			break;
		case SDL_MOUSEBUTTONUP:
			this->mouseButtonUpEvent(i);
			break;
		case SDL_WINDOWEVENT:
			switch (this->_frameEvents.at(i).window.event)
			{
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				this->windowFocusGainEvent(i);
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				this->windowFocusLossEvent(i);
				break;
			case (SDL_WINDOWEVENT_SIZE_CHANGED || SDL_WINDOWEVENT_RESIZED):
				this->windowSizeChangeEvent(i);
				break;
			case SDL_WINDOWEVENT_MOVED:
				this->windowMoveEvent(i);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void Input::keyDownEvent(size_t &index)
{
	std::cout << "Pressed key " << this->_frameEvents[index].key.keysym.scancode << "!\n";
	this->_pressedKeys[this->_frameEvents[index].key.keysym.scancode] = true;
	this->_heldKeys[this->_frameEvents[index].key.keysym.scancode] = true;
}

void Input::keyHeldEvent(size_t &index)
{
	// Uh, not much to do here when keys are held down...
}

void Input::keyUpEvent(size_t &index)
{
	this->_releasedKeys[this->_frameEvents[index].key.keysym.scancode] = true;
	this->_heldKeys[this->_frameEvents[index].key.keysym.scancode] = false;
}

void Input::mouseMotionEvent(size_t &index)
{
	this->_cursorX = this->_frameEvents[index].motion.x;
	this->_cursorY = this->_frameEvents[index].motion.y;
	this->_cursorMovedX = this->_frameEvents[index].motion.xrel;
	this->_cursorMovedY = this->_frameEvents[index].motion.yrel;
}

void Input::mouseScrollEvent(size_t &index)
{
	this->_scrolledX = this->_frameEvents[index].wheel.x;
	this->_scrolledY = this->_frameEvents[index].wheel.y;
}

void Input::mouseButtonDownEvent(size_t &index)
{
	this->_pressedMouseButtons[this->_frameEvents[index].button.button] = true;
}

void Input::mouseButtonUpEvent(size_t &index)
{
	this->_releasedMouseButtons[this->_frameEvents[index].button.button] = true;
}

void Input::windowFocusGainEvent(size_t &index)
{
	std::cout << "Window gained focus!\n";
	this->_windowInFocus = true;
}

void Input::windowFocusLossEvent(size_t &index)
{
	std::cout << "Window lost focus!\n";
	this->_windowInFocus = false;
}

void Input::windowSizeChangeEvent(size_t &index)
{
	std::cout << "Window size was changed!\n";
	this->_windowSizeChanged = true;
}

void Input::windowMoveEvent(size_t &index)
{
	std::cout << "Window was moved!\n";
	this->_windowMoved = true;
}
