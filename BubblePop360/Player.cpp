#include "Player.hpp"

void Player::movement()
{
    objSprite->setScale(sf::Vector2f(0.1f, 0.1f));

    objSprite->setOrigin(sf::Vector2f(arrowTexture.getSize().x * 0.5, arrowTexture.getSize().y * 1));

    objSprite->setPosition(sf::Vector2f(524.f, 384.f));

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

void Player::spawnBall(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects)
{
    static bool spacePressedLastFrame = false;

    bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space);
    if (!spacePressedLastFrame && isSpacePressed)
    {
        objects[objects.size() - 1]->shoot(arrowRotation - 90);
        newObjects.emplace_back(std::make_unique<Ball>(arrowRotation - 90));
    }
    spacePressedLastFrame = isSpacePressed;
}

void Player::checkGame(vector<std::unique_ptr<Object>>& objects)
{
    for (size_t i = 1; i < objects.size(); ++i)
    {
        float dx = this->objSprite->getPosition().x - objects[i]->objSprite->getPosition().x;
        float dy = this->objSprite->getPosition().y - objects[i]->objSprite->getPosition().y;

        float distanceSquared = dx * dx + dy * dy;
        float radiusSquared = (32 + 32) * (32 + 32);

        if (!(objects[i]->justSpawned) && distanceSquared <= radiusSquared)
        {
            state = gameState::End;
        }
    }
}

void Player::update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects)
{
    movement();

    spawnBall(newObjects, objects);

    checkGame(objects);
}
	
