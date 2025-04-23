#include "Ball.hpp"

sf::Texture Ball::redBallTexture;
sf::Texture Ball::blueBallTexture;
sf::Texture Ball::yellowBallTexture;

void Ball::move()
{
	if (isMoving)
	{
		velocity.x = 6.7f * std::cos(direction);
		velocity.y = 6.7f * std::sin(direction);
	}

	pos = this->objSprite->getPosition();

	if (pos.x <= 0 || pos.x + 64 >= 1024) 
	{
		velocity.x = 0;
		velocity.y = 0;
		isMoving = false;
	}

	pos = this->objSprite->getPosition();

	if (pos.y <= 0 || pos.y + 65 >= 768) 
	{
		velocity.x = 0;
		velocity.y = 0;
		isMoving = false;
	}

	objSprite->move(velocity);
}

void Ball::update(vector<std::unique_ptr<Object>>& objects)
{
	move();
}
