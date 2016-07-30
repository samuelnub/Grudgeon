#include <Handler/settings.h>
#include <Game/game.h>
#include <iostream>

Settings::Settings()
{
}

Settings::~Settings()
{
	this->_xmlDoc->SaveFile(this->_filePath);
	this->_xmlDoc.reset();
}

void Settings::init(Game * game)
{
	this->_game = game;

	this->_filePath = "Resources/Settings/settings.xml";

	// The xml doc remains open throughout the game, and gets saved to file at the end when the destructor's called
	this->_xmlDoc = std::make_unique<tinyxml2::XMLDocument>();
	tinyxml2::XMLError xmlError = this->_xmlDoc->LoadFile(this->_filePath);
	if (xmlError != 0)
	{
		std::cout << "Couldn't load settings from " << this->_filePath << "!\n";
		return;
	}

	this->map();
}

int Settings::write(std::string settingName, std::string value)
{
	return 0;
}

int Settings::map()
{
	tinyxml2::XMLElement *xmlEle = this->_xmlDoc->FirstChildElement("root");

	if (xmlEle != nullptr)
	{
		xmlEle = xmlEle->FirstChildElement("setting");
		if (xmlEle != nullptr)
		{
			while (xmlEle)
			{
				std::string settingName;
				settingName = xmlEle->Attribute("name");

				std::string valueString;
				valueString = xmlEle->Attribute("value");

				this->_settings[settingName] = valueString;
				std::cout << "Just got the value " << valueString << " from " << settingName << " for settings!\n";

				xmlEle = xmlEle->NextSiblingElement("setting");
			}
		}
	}

	return 0;
}
