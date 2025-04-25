#pragma once
#include "Ball.hpp"

// Player will handle controls of Player and create Ball objects
class Player : public Object
{
private:
	void movement(); // movement of the player/arrow
	void spawnBall(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects); // spawns the ball that the player is about to shoot
	void spawnBorderBalls(float screenWidth, float screenHeight, float ballSize, std::vector<std::unique_ptr<Object>>& newObjects, std::vector<std::unique_ptr<Object>>& objects); // Spawns a layer of non-player balls after the starting layer
	void spawnStartingLayer(vector<std::unique_ptr<Object>>& newObjects); // Spawns starting layer of non-player balls
	bool isSpaceFree(sf::Vector2f pos, float ballSize, const std::vector<std::unique_ptr<Object>>& objects, const std::vector<std::unique_ptr<Object>>& newObjects); // used in spawnBorderBalls, fixes the overlapping issue


	sf::Texture arrowTexture;
	float arrowRotation;
	
	sf::Music shootsound;
	int shotCounter;


public:
	Player() 
	{ 
		isPlayer = false;
		state = gameState::Running;

		arrowTexture.loadFromFile("../assets/arrow.png");
		shootsound.openFromFile("../assets/shootsound.ogg");
		objSprite= sf::Sprite(arrowTexture);
		arrowRotation = 0.0;
		points = 0.0;
		ballCount = 0;
		noMovement = true;
	}

	void checkGame(vector<std::unique_ptr<Object>>& objects); // handles game over sequence
	void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) override;
};