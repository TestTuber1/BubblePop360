#pragma once
#include "header.hpp"

// Object will be the entity for every object in the game
class Object
{
public:
	gameState state; //is the game running or not?
	std::optional<sf::Sprite> objSprite; //sprite cannot be instantiated with null. This defines a sprite object as "optional," but objSprite will be used in our game
	sf::Vector2f velocity; //vector2f is a set of two values. We will use it as velocity

	// for the ball
	bool isMoving;
	bool justSpawned;
	bool isCollidable;
	bool isPlayer;
	int ballColor;

	// for the player
	double points;
	int ballCount;

	Object() //constructor
	{
		state = gameState::End; //at instantiation, the game is not considered to be running
		velocity = { 0,0 };
	}
	virtual ~Object() {} //destructor may be overriden, based upon what derived type of object, object is

	virtual void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) {} //as in, update an object by means of the object's pointers. will be overriden.
	virtual void shoot(float arrowRotation) {}
};
