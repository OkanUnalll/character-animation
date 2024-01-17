#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(std::string spritesheetDir, sf::IntRect rect);

private:
	std::string spritesheetDir;
	sf::IntRect rect;
};