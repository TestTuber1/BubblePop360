#include "Ball.hpp"

sf::Texture Ball::redBallTexture;
sf::Texture Ball::blueBallTexture;
sf::Texture Ball::yellowBallTexture;

void Ball::move()
{
	velocity.x = 6.7f * std::cos(direction);
	velocity.y = 6.7f * std::sin(direction);
	objSprite->move(velocity);
}

void Ball::update(vector<std::unique_ptr<Object>>& objects)
{
	if (isPlayer)
		move();
}
