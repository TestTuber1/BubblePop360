#include "Player.hpp"

void Player::movement()
{
    objSprite->setScale(sf::Vector2f(0.1f, 0.1f));

    objSprite->setOrigin(sf::Vector2f(arrowTexture.getSize().x * 0.5, arrowTexture.getSize().y * 1));

    objSprite->setPosition(sf::Vector2f(514.f, 384.f));

    float rotationSpeed = 3.25;
    AnimationPhase arrowPhase = AnimationPhase::None;
    bool wasRightPressed = false;

    bool isRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right);
    if (isRightPressed)  
        arrowRotation += rotationSpeed;
    bool isLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left);
    if (isLeftPressed)
        arrowRotation -= rotationSpeed;
    wasRightPressed = isRightPressed;

    objSprite->setRotation(sf::degrees(arrowRotation));
}

void Player::spawnBall(vector<std::unique_ptr<Object>>& objects)
{
    static bool spacePressedLastFrame = false;

    bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space);
    if (!spacePressedLastFrame && isSpacePressed)
    {
        objects.emplace_back(std::make_unique<Ball>(arrowRotation - 90));
    }
    spacePressedLastFrame = isSpacePressed;
}

void Player::update(vector<std::unique_ptr<Object>>& objects)
{
    movement();
    spawnBall(objects);
}
	
