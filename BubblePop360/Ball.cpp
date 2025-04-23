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
		justSpawned = false;
	}

	pos = this->objSprite->getPosition();

	if (pos.y <= 0 || pos.y + 65 >= 768) 
	{
		velocity.x = 0;
		velocity.y = 0;
		isMoving = false;
		justSpawned = false;
	}

	objSprite->move(velocity);
}

void Ball::checkBallCollision(std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2) {
	Ball* ball1 = dynamic_cast<Ball*>(obj1.get());
	Ball* ball2 = dynamic_cast<Ball*>(obj2.get());

	if (!ball1 || !ball2) 
	{
		return;
	}

	if (!(ball1->isCollidable) || !(ball2->isCollidable))
		return;

	float dx = ball1->objSprite->getPosition().x - ball2->objSprite->getPosition().x;
	float dy = ball1->objSprite->getPosition().y - ball2->objSprite->getPosition().y;
	float distanceSquared = dx * dx + dy * dy;
	float radiusSquared = (32 + 32) * (32 + 32);

	if (distanceSquared <= radiusSquared) 
	{
		ball1->velocity.x = 0;
		ball1->velocity.y = 0;
		ball1->isMoving = false;
		ball1->justSpawned = false;

		ball2->velocity.x = 0;
		ball2->velocity.y = 0;
		ball2->isMoving = false;
		ball2->justSpawned = false;
	}
}

void Ball::shoot(float arrowRotation)
{
	isMoving = true;
	isCollidable = true;
	direction = arrowRotation * (pi / 180.0f);
}

void Ball::update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects)
{
	move();

	for (size_t i = 0; i < objects.size(); ++i) 
	{
		for (size_t j = i + 1; j < objects.size(); ++j) 
		{
			checkBallCollision(objects[i], objects[j]);
		}
	}
}
