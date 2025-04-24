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
		noMovement = true;
	}

	else if (pos.y <= 0 || pos.y + 65 >= 768) 
	{
		velocity.x = 0;
		velocity.y = 0;
		isMoving = false;
		justSpawned = false;
		noMovement = true;
	}

	objSprite->move(velocity);
}

void Ball::checkBallCollision(std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2, vector<std::unique_ptr<Object>>& objects) {
	Ball* ball1 = dynamic_cast<Ball*>(obj1.get());
	Ball* ball2 = dynamic_cast<Ball*>(obj2.get());

	if (!ball1 || !ball2 || !ball1->isCollidable || !ball2->isCollidable)
		return;

	float dx = ball1->objSprite->getPosition().x - ball2->objSprite->getPosition().x;
	float dy = ball1->objSprite->getPosition().y - ball2->objSprite->getPosition().y;
	float distanceSquared = dx * dx + dy * dy;
	float radiusSquared = (32 + 32) * (32 + 32);

	if (distanceSquared <= radiusSquared) 
	{
		if ((ball1->isPlayer == true || ball2->isPlayer == true) && (ball1->ballColor == ball2->ballColor))
		{
			Ball* base = ball1->isPlayer ? ball1 : ball2;
			std::vector<Ball*> connectedGroup;
			connectedBalls(base, objects, connectedGroup);

			if (connectedGroup.size() >= 3)
			{
				objects[0]->points += (100.0 * connectedGroup.size() * (1 + (connectedGroup.size() * 0.1 - 0.3)));

				for (auto it = objects.begin(); it != objects.end(); )
				{
					Ball* b = dynamic_cast<Ball*>(it->get());
					if (std::find(connectedGroup.begin(), connectedGroup.end(), b) != connectedGroup.end())
						it = objects.erase(it);
					else
						++it;
				}
			}
		}
		ball1->velocity.x = 0;
		ball1->velocity.y = 0;
		ball1->isMoving = false;
		ball1->isPlayer = false;
		ball1->justSpawned = false;

		ball2->velocity.x = 0;
		ball2->velocity.y = 0;
		ball2->isMoving = false;
		ball2->isPlayer = false;
		ball2->justSpawned = false;

		noMovement = true;
	}

}

void Ball::connectedBalls(Ball* start, vector<std::unique_ptr<Object>>& objects, std::vector<Ball*>& group)
{
	std::queue<Ball*> toVisit; // queue of balls that will get checked
	std::unordered_set<Ball*> visited; // set of balls that have already been checked and have the same color as the starting ball

	toVisit.push(start);
	visited.insert(start);

	while (!toVisit.empty())
	{
		Ball* current = toVisit.front();
		toVisit.pop();
		group.push_back(current);

		for (auto& obj : objects)
		{
			Ball* neighbor = dynamic_cast<Ball*>(obj.get());
			if (!neighbor || visited.count(neighbor) || neighbor->ballColor != start->ballColor)
				continue;

			float dx = current->objSprite->getPosition().x - neighbor->objSprite->getPosition().x;
			float dy = current->objSprite->getPosition().y - neighbor->objSprite->getPosition().y;
			float distanceSquared = dx * dx + dy * dy;
			float radiusSquared = (32 + 32) * (32 + 32);

			if (distanceSquared <= radiusSquared)
			{
				toVisit.push(neighbor);
				visited.insert(neighbor);
			}
		}
	}
}

void Ball::shoot(float arrowRotation)
{
	isMoving = true;
	isPlayer = true;
	isCollidable = true;
	direction = arrowRotation * (pi / 180.0f);
	noMovement = false;
}

void Ball::update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects)
{
	if (!isMoving && !isPlayer)
		return;
	if (shootable)
	{
		move();
	}

	for (size_t i = 0; i < objects.size(); ++i) 
	{
		if (!isMoving) isPlayer = false;
		for (size_t j = i + 1; j < objects.size(); ++j) 
		{
			checkBallCollision(objects[i], objects[j], objects);
		}
	}

}
