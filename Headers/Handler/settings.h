#pragma once
#ifndef HANDLER_SETTINGS_H
#define HANDLER_SETTINGS_H

#include <tinyxml2/tinyxml2.h>

#include <unordered_map>
#include <string>
#include <boost/lexical_cast.hpp>
#include <memory>

class Game;

class Settings
{
public:
	Settings();
	~Settings();

	void init(Game *game);

	int write(std::string settingName, std::string value);

	// Get your setting, casted to your defined type, yea I know, not very efficient to cast, but the time complexity for string conversion should be O(n) and its usually just a few chars to convert - so thats my lame excuse
	inline bool getBool(std::string name)
	{
		return boost::lexical_cast<bool>(this->_settings.at(name));
	}

	inline int getInt(std::string name)
	{
		return boost::lexical_cast<int>(this->_settings.at(name));
	}

	inline float getFloat(std::string name)
	{
		return boost::lexical_cast<float>(this->_settings.at(name));
	}

	inline std::string getString(std::string name)
	{
		return this->_settings.at(name);
	}

private:
	Game *_game;

	const char *_filePath;

	std::unique_ptr<tinyxml2::XMLDocument> _xmlDoc;

	std::unordered_map<std::string, std::string> _settings;

	// initial read to map
	int map();

protected:


};

#endif