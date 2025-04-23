#include "header.hpp"

// Object will be the entity for every object in the game
class Object
{
public:
	gameState state;
	std::optional<sf::Sprite> objSprite;
	sf::Vector2f velocity;
	bool isMoving;

	Object() 
	{
		state = gameState::End;
		velocity = { 0,0 };
	}
	virtual ~Object() {}

	virtual void update(vector<std::unique_ptr<Object>>& objects) {}
};
