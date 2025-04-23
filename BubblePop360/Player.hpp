#include "Ball.hpp"

// Player will handle controls of Player and create Ball objects
class Player : public Object
{
private:
	void movement();
	void spawnBall(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects);
	void checkGame(vector<std::unique_ptr<Object>>& objects);

	sf::Texture arrowTexture;
	float arrowRotation;
public:
	Player() 
	{ 
		state = gameState::Running;

		arrowTexture.loadFromFile("../assets/arrow.png");
		objSprite= sf::Sprite(arrowTexture);
		arrowRotation = 0.0;
	}
	void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) override;
};