#include "header.hpp"

// Object will be the entity for every object in the game
class Object
{
public:
	gameState state;
	std::optional<sf::Sprite> objSprite;

	Object() 
	{
		state = gameState::End;
	}
	virtual ~Object() {}

	virtual void update(vector<std::unique_ptr<Object>>& objects) {}
};
