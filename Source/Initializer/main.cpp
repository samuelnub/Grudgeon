#include <Game/game.h>
#include <iostream>

int main(int argc, char *args[])
{
	std::cout << "ayy\n";
	try
	{
		Game game;
	}
	catch (const char *error)
	{
		std::cout << "Encountered exception!\n" << error << "\n";
	}
	
	std::cout << "lmao\n";
	return 0;
}