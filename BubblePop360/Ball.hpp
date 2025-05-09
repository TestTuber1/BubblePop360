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
	void checkBallCollision(std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2, vector<std::unique_ptr<Object>>& objects); // checks the collided balls and pops them if they're the same color, goes down the chain of balls that have the same color
	void connectedBalls(Ball* start, vector<std::unique_ptr<Object>>& objects, std::vector<Ball*>& group); // collects the connected balls for checkBallCollision to go through
	float direction;
	sf::Vector2f pos;
public:
	bool isBorderBall = false;
	bool isCollidable = true;
	bool shootable;

	void shoot(float arrowRotation);

	Ball(float arrowRotation)
	{
		isPlayer = false;
		isMoving = false;
		justSpawned = true;
		isCollidable = false;
		shootable = true;
		readyToJoinVector = true;
		direction = arrowRotation * (pi / 180.0f);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(1, 3);

		int random_color = distr(gen);
		ballColor = random_color;
		switch (ballColor)
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

		objSprite->setScale(sf::Vector2f(0.25f, 0.25f));
		objSprite->setPosition(sf::Vector2f(491.5f, 354.f));
	}

	void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) override;

	static void loadTextures() // loads the textures of the colors
	{
		redBallTexture.loadFromFile("../assets/redBall.png");
		blueBallTexture.loadFromFile("../assets/blueBall.png");
		yellowBallTexture.loadFromFile("../assets/yellowBall.png");
	}
};