#include "Game.h"

// --- PUBLIC --- //
// - Constructor
Game::Game() {
	this->initVariables();
	this->initWindow();
};

// - Accessors
bool Game::isRunning() const {
	return this->window.isOpen();
}

// - Render & Update
void Game::initGameLoop() {
	while (this->isRunning()) {
		// - Update Game
		this->update();

		// - Render Game
		this->render();
	}
}

void Game::pollEvents() {
	while (this->window.pollEvent(this->event)) {
		switch (event.type) {
		case sf::Event::Closed:
			this->window.close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				window.close();
		}
	}
}

void Game::update() {
	this->pollEvents();
}

void Game::render() {
	// Init Update Functions
	this->player.setPositionY(float(this->videoMode.height / 2));
	this->player.update();

	// - Clear Game Background
	this->window.clear(sf::Color::Black);

	// - Draw / Render Game Objects
	this->player.render(this->window);

	// - Display Window
	this->window.display();
}

// --- PRIVATE --- //
// - Init Functions
void Game::initVariables() {
	// - Window
	this->fpsLimit = 60;
	this->windowTitle = "SFML Game Demo";
	// - Video Mode
	this->videoMode.width = 800; // window width
	this->videoMode.height = 600; // window height
}

void Game::initWindow() {
	this->window.create(this->videoMode, this->windowTitle);
	this->window.setFramerateLimit(this->fpsLimit);
}