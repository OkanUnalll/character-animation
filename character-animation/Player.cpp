#include "Player.h"

// --- PUBLIC --- //
// - Constructor
Player::Player() {
    this->initVariables();
    this->initTextures();
    this->initPlayer();
}

// - Render & Update
void Player::render(sf::RenderWindow& window) {
    window.draw(this->player);
}

void Player::update() {
    // - Init Player Controls
    this->initControls();

    // - Update Player Animation
    if (this->clock.getElapsedTime().asMilliseconds() > this->animationSpeed) {
        this->currentFrame = (this->currentFrame + 1) % this->frameCount;
        this->player.setTextureRect(sf::IntRect(this->currentFrame * this->frameWidth, 0, this->frameWidth, this->frameHeight));
        this->clock.restart();
    }
}

// - Player
void Player::setSpeed(float speed) {
    this->speed = speed;
}
void Player::setPosition(float x, float y) {
    this->player.setPosition(x, y);
}

void Player::setPositionX(float position) {
    this->player.setPosition(position, this->player.getPosition().y);
}

void Player::setPositionY(float position) {
    this->player.setPosition(this->player.getPosition().x, position);
}

// - Actions
void Player::idle(CurrentDirection direction = CurrentDirection::RIGHT) {
    this->isRunning = false;
    this->frameCount = 4;

    switch (direction) {
    case CurrentDirection::LEFT:
        this->player.setTexture(this->idleLeftTexture);
        break;
    case CurrentDirection::RIGHT:
        this->player.setTexture(this->idleRightTexture);
        break;
    }
}

void Player::walk(CurrentDirection direction = CurrentDirection::RIGHT) {
    this->setFrameCount(7);

    switch (direction) {
    case CurrentDirection::LEFT:
        this->player.setTexture(this->walkLeftTexture);
        this->player.move(-this->speed, 0);
        break;
    case CurrentDirection::RIGHT:
        this->player.setTexture(this->walkRightTexture);
        this->player.move(this->speed, 0);
        break;
    }
}

void Player::run(CurrentDirection direction = CurrentDirection::RIGHT) {
    this->setFrameCount(7);

    switch (direction) {
    case CurrentDirection::LEFT:
        this->player.setTexture(this->runLeftTexture);
        this->player.move(-(this->speed * 3), 0);
        break;
    case CurrentDirection::RIGHT:
        this->player.setTexture(this->runRightTexture);
        this->player.move(this->speed * 3, 0);
        break;
    }
}

void Player::simpleAttack(CurrentDirection direction = CurrentDirection::RIGHT) {
    this->setFrameCount(5);

    switch (direction) {
    case CurrentDirection::LEFT:
        this->player.setTexture(this->attack1LeftTexture);
        break;
    case CurrentDirection::RIGHT:
        this->player.setTexture(this->attack1RightTexture);
        break;
    }
}

void Player::heavyAttack(CurrentDirection direction = CurrentDirection::RIGHT) {
    this->setFrameCount(4);

    switch (direction) {
    case CurrentDirection::LEFT:
        this->player.setTexture(this->attack2LeftTexture);
        break;
    case CurrentDirection::RIGHT:
        this->player.setTexture(this->attack2RightTexture);
        break;
    }
}

void Player::defence(CurrentDirection direction = CurrentDirection::RIGHT) {
    this->setFrameCount(5);

    switch (direction) {
    case CurrentDirection::LEFT:
        this->player.setTexture(this->defenceLeftTexture);
        break;
    case CurrentDirection::RIGHT:
        this->player.setTexture(this->defenceRightTexture);
        break;
    }
}

// - Animation
void Player::setFrameCount(unsigned int count) {
    this->frameCount = count;
}
void Player::setAnimationSpeed(int animationSpeed) {
    this->animationSpeed = animationSpeed;
}
void Player::setCurrentFrame(unsigned int currentFrame) {
    this->currentFrame = currentFrame;
}

// - Controls
void Player::disableUserControls() {
    this->isUserControlsDisabled = true;
}

void Player::enableUserControls() {
    this->isUserControlsDisabled = false;
}

// --- PRIVATE --- //
void Player::initVariables() {
    // - Player
    this->speed = 2.0f;
    this->positionX = 0.0f;
    this->positionY = 0.0f;

    // - Animation
    this->frameWidth = 128; // current image width
    this->frameHeight = 128; // current image height
    this->frameCount = 4; // image count in texture
    this->animationSpeed = 100; // lower value means faster animation
    this->currentFrame = 0;
    this->currentDirection = CurrentDirection::RIGHT;

    // - Movement
    this->isRunning = false;

    // - Controls
    this->isUserControlsDisabled = false;
}

void Player::initTextures() {
    this->idleLeftTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Idle-Left.png");
    this->idleRightTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Idle-Right.png");

    this->walkLeftTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Walk-Left.png");
    this->walkRightTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Walk-Right.png");

    this->runLeftTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Run-Left.png");
    this->runRightTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Run-Right.png");

    this->defenceLeftTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Defend-Left.png");
    this->defenceRightTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Defend-Right.png");

    this->attack1LeftTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Attack-1-Left.png");
    this->attack1RightTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Attack-1-Right.png");

    this->attack2LeftTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Attack-2-Left.png");
    this->attack2RightTexture.loadFromFile("assets\\textures\\knights\\Knight_1\\Attack-2-Right.png");
}

void Player::initPlayer() {
    this->player.setTexture(idleRightTexture);
    this->player.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void Player::initControls() {
    if (!this->isUserControlsDisabled) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            // start run animation
            this->isRunning = true;
        }
        
        // - Simple Attack
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->simpleAttack(this->currentDirection);
        }
        // - Heavy Attack
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            this->heavyAttack(this->currentDirection);
        }
        // - Defence
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            this->defence(this->currentDirection);
        }
        // - Move Left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->currentDirection = CurrentDirection::LEFT;

            switch (this->isRunning) {
            case false:
                this->walk(CurrentDirection::LEFT);
                break;
            case true:
                this->run(CurrentDirection::LEFT);
            }
        }
        // - Move Right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->currentDirection = CurrentDirection::RIGHT;

            switch (this->isRunning) {
            case false:
                this->walk(CurrentDirection::RIGHT);
                break;
            case true:
                this->run(CurrentDirection::RIGHT);
            }
        }
        // - Idle
        else {
            this->idle(currentDirection);
        }
    }
}