#pragma once
#include "header.hpp"

// Object will be the entity for every object in the game
class Object
{
public:
	gameState state;
	std::optional<sf::Sprite> objSprite;
	sf::Vector2f velocity;

	// for the ball
	bool isMoving;
	bool justSpawned;
	bool isCollidable;
	bool isPlayer;
	int ballColor;
	bool readyToJoinVector;

	// for the player
	double points;
	int ballCount;
	bool hasSpawnedLayer = false;
	int borderLayerCount = 0;
	static bool noMovement;

	Object() 
	{
		state = gameState::End;
		velocity = { 0,0 };
	}
	virtual ~Object() {}

	virtual void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) = 0; // pure virtual, only called by other classes
	virtual void shoot(float arrowRotation) {}
};
