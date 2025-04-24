#pragma once
#include "Object.hpp"

// Ball will exist and pop on direct/indirect contact with a isPlayer = true Ball
class Ball : public Object
{
private:
	static sf::Texture redBallTexture;
	static sf::Texture blueBallTexture;
	static sf::Texture yellowBallTexture;

	void move();
	void checkBallCollision(std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2, vector<std::unique_ptr<Object>>& objects);
	void connectedBalls(Ball* start, vector<std::unique_ptr<Object>>& objects, std::vector<Ball*>& group);
	// collects the connected balls for checkBallCollision to go through
	float direction;
	sf::Vector2f pos;
public:
	void shoot(float arrowRotation);

	Ball(float arrowRotation)
	{
		isPlayer = false;
		isMoving = false;
		justSpawned = true;
		isCollidable = false;
		direction = arrowRotation * (pi / 180.0f);

		std::random_device rd; //random seed generator for std::mt19937
		std::mt19937 gen(rd()); //random number generator. works similarly to the combination of srand() and rand()
		std::uniform_int_distribution<> distr(1, 3); //random integer with the range of 1-3

		int random_color = distr(gen);
		ballColor = random_color;
		switch (ballColor) //when a ball spawns, the color should be randomized. a ball may be red, blue, or yellow.
		{
		case 1:
			objSprite = sf::Sprite(redBallTexture);
			break;
		case 2:
			objSprite = sf::Sprite(blueBallTexture);
			break;
		case 3:
			objSprite = sf::Sprite(yellowBallTexture);
			break;
		}

		objSprite->setScale(sf::Vector2f(0.25f, 0.25f)); //set the size of the ball
		objSprite->setPosition(sf::Vector2f(491.5f, 354.f)); //and the position of the ball
	}

	void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) override; //overriden function of object class

	static void loadTextures() //read png from resource files folder of our solution
	{
		redBallTexture.loadFromFile("../assets/redBall.png"); 
		blueBallTexture.loadFromFile("../assets/blueBall.png");
		yellowBallTexture.loadFromFile("../assets/yellowBall.png");
	}
};