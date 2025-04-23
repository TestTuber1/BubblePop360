#include "Object.hpp"

// Ball will exist and pop on direct/indirect contact with a isPlayer = true Ball
class Ball : public Object
{
private:
	static sf::Texture redBallTexture;
	static sf::Texture blueBallTexture;
	static sf::Texture yellowBallTexture;

	void move();
	void checkBallCollision(std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2);

	float direction;
	sf::Vector2f pos;
public:
	void shoot(float arrowRotation);

	Ball() 
	{
		isPlayer = false;
		isMoving = false;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(1, 3);

		int random_color = distr(gen);
		switch (random_color)
		{
		case 1:
			ballColor = Color::Red;
			objSprite = sf::Sprite(redBallTexture);
			break;
		case 2:
			ballColor = Color::Blue;
			objSprite = sf::Sprite(blueBallTexture);
			break;
		case 3:
			ballColor = Color::Yellow;
			objSprite = sf::Sprite(yellowBallTexture);
			break;
		}

		objSprite->setScale(sf::Vector2f(0.25f, 0.25f));
		objSprite->setPosition(sf::Vector2f(464.f, 384.f));
	}

	Ball(float arrowRotation)
	{
		isPlayer = true;
		isMoving = false;
		justSpawned = true;
		isCollidable = false;
		direction = arrowRotation * (pi / 180.0f);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(1, 3);

		int random_color = distr(gen);
		switch (random_color)
		{
		case 1:
			ballColor = Color::Red;
			objSprite = sf::Sprite(redBallTexture);
			break;
		case 2:
			ballColor = Color::Blue;
			objSprite = sf::Sprite(blueBallTexture);
			break;
		case 3:
			ballColor = Color::Yellow;
			objSprite = sf::Sprite(yellowBallTexture);
			break;
		}

		objSprite->setScale(sf::Vector2f(0.25f, 0.25f));
		objSprite->setPosition(sf::Vector2f(481.5f, 354.f));
	}

	void update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects) override;

	static void loadTextures()
	{
		redBallTexture.loadFromFile("../assets/redBall.png");
		blueBallTexture.loadFromFile("../assets/blueBall.png");
		yellowBallTexture.loadFromFile("../assets/yellowBall.png");
	}
};