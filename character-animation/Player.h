#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class CurrentDirection {
    LEFT,
    RIGHT,
};

class Player {
public:
    Player();

    // --- FUNCTIONS --- //
    // - Render & Update
    void render(sf::RenderWindow& window);
    void update();

    // - Player
    void setSpeed(float speed);
    void setPosition(float x, float y);
    void setPositionX(float position);
    void setPositionY(float position);

    // - Actions
    void idle(CurrentDirection direction);
    void walk(CurrentDirection direction);
    void run(CurrentDirection direction);
    void simpleAttack(CurrentDirection direction);
    void heavyAttack(CurrentDirection direction);
    void defence(CurrentDirection direction);

    // - Animation
    void setFrameCount(unsigned int count);
    void setAnimationSpeed(int animationSpeed);
    void setCurrentFrame(unsigned int currentFrame);

    // - Controls
    void disableUserControls();
    void enableUserControls();

private:
    // --- VARIABLES --- //
    // - Player
    sf::Sprite player;
    float speed;
    float positionX;
    float positionY;
    
    // - Animation
    int frameWidth; // current image width
    int frameHeight; // current image height
    int frameCount; // image count in texture
    int animationSpeed; // lower value means faster animation
    int currentFrame;
    CurrentDirection currentDirection;

    // - Movement
    bool isRunning;
    
    // - Controls
    bool isUserControlsDisabled;
    
    // - Textures
    sf::Texture idleLeftTexture;
    sf::Texture idleRightTexture;
    sf::Texture walkLeftTexture;
    sf::Texture walkRightTexture;
    sf::Texture runLeftTexture;
    sf::Texture runRightTexture;
    sf::Texture defenceLeftTexture;
    sf::Texture defenceRightTexture;
    sf::Texture attack1LeftTexture;
    sf::Texture attack1RightTexture;
    sf::Texture attack2LeftTexture;
    sf::Texture attack2RightTexture;
    
    // - Helpers
    sf::Clock clock;

    // --- FUNCTIONS --- //
    // - Init Functions
    void initVariables();
    void initTextures();
    void initPlayer();
    void initControls();
};