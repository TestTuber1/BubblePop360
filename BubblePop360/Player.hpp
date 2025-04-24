#pragma once
#include "Ball.hpp"

// Player will handle controls of Player and create Ball objects
class Player : public Object
{
private:
	void movement();
	void spawnBall(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects);
	void spawnBorderBalls(float screenWidth, float screenHeight, float ballSize, std::vector<std::unique_ptr<Object>>& newObjects, sf::Texture& tecture);
	void spawnStartingLayer(vector<std::unique_ptr<Object>>& newObjects);

	sf::Texture arrowTexture;
	float arrowRotation;
	
	sf::Music shootsound;
	int shotCounter;
	bool hasSpawnedLayer = false;
	int borderLayerCount = 0;


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
		shotCounter = 0;
	}

	void checkGame(vector<std::unique_ptr<Object>>& objects);
	void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) override;
};