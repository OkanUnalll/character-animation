#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"

class Game {
public:
	// - Constructor
	Game();

	// --- FUNCTIONS --- //
	// - Accessors
	bool isRunning() const;

	// - Render & Update
	void initGameLoop(); // (!) game loop
	void pollEvents(); // event listener loop
	void update(); // event loops and other updates...
	void render(); // draw & display tasks...

private:
	// --- VARIABLES --- //
	// - Helpers
	sf::RenderWindow window;
	sf::Event event;
	sf::VideoMode videoMode;

	// - Window
	unsigned int fpsLimit;
	std::string windowTitle;

	// - Player
	Player player;

	// --- FUNCTIONS --- //
	// - Init Functions
	void initVariables();
	void initWindow();
};

