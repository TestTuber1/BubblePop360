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

        sf::Texture texture;

        this->shotCounter++;
        if (this->shotCounter >= 6)
        {
            this->borderLayerCount++;
            spawnBorderBalls(1024.0f, 768.0f, 64.0f, newObjects, texture);
            this->shotCounter = 0;
        }
        //std::cout << "asfsd";

        shootsound.play();

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

void Player::spawnBorderBalls(float screenWidth, float screenHeight, float ballSize, std::vector<std::unique_ptr<Object>>& newObjects, sf::Texture& texture)
{
    float offset = borderLayerCount * ballSize;

    for (float x = offset; x <= screenWidth - ballSize - offset; x += ballSize)
    {
        int colorID = rand() % 3;

        auto topBall = std::make_unique<Ball>(0.0f);
        topBall->objSprite->setPosition(sf::Vector2f(x, offset));
        topBall->isBorderBall = true;
        topBall->isCollidable = true;

        newObjects.push_back(std::move(topBall));

        auto bottomBall = std::make_unique<Ball>(0.0f);
        bottomBall->objSprite->setPosition(sf::Vector2f(x, screenHeight - ballSize - offset));
        bottomBall->isBorderBall = true;
        bottomBall->isCollidable = true;

        newObjects.push_back(std::move(bottomBall));
    }

    for (float y = offset + ballSize; y < screenHeight - ballSize - offset; y += ballSize)
    {
        int colorID = rand() % 3;

        auto leftBall = std::make_unique<Ball>(0.0f);
        leftBall->objSprite->setPosition(sf::Vector2f(offset, y));
        leftBall->isBorderBall = true;
        leftBall->isCollidable = true;

        newObjects.push_back(std::move(leftBall));

        auto rightBall = std::make_unique<Ball>(0.0f);
        rightBall->objSprite->setPosition(sf::Vector2f(screenWidth - ballSize - offset, y));
        rightBall->isBorderBall = true;
        rightBall->isCollidable = true;

        newObjects.push_back(std::move(rightBall));
    }
}

void Player::spawnStartingLayer(vector<std::unique_ptr<Object>>& newObjects)
{
    const float ballSize = 64.f;
    const float width = 1050.f;
    const float height = 768.f;

    // Top edge (left to right)
    for (float x = 0.f; x <= width - ballSize; x += ballSize)
    {
        auto ball = std::make_unique<Ball>(0.f);
        ball->objSprite->setPosition(sf::Vector2f(x, 0.f));
        ball->velocity = sf::Vector2f(0.f, 0.f);
        ball->isCollidable = true;
        ball->isBorderBall = true;
        newObjects.emplace_back(std::move(ball));
    }

    // Right edge (top to bottom) — skip top and bottom corners
    for (float y = ballSize; y <= height - ballSize * 2; y += ballSize)
    {
        auto ball = std::make_unique<Ball>(0.f);
        ball->objSprite->setPosition(sf::Vector2f(width - ballSize, y));
        ball->velocity = sf::Vector2f(0.f, 0.f);
        ball->isCollidable = true;
        ball->isBorderBall = true;
        newObjects.emplace_back(std::move(ball));
    }

    // Bottom edge (right to left)
    for (float x = width - ballSize; x >= 0.f; x -= ballSize)
    {
        auto ball = std::make_unique<Ball>(0.f);
        ball->objSprite->setPosition(sf::Vector2f(x, height - ballSize));
        ball->velocity = sf::Vector2f(0.f, 0.f);
        ball->isCollidable = true;
        ball->isBorderBall = true;
        newObjects.emplace_back(std::move(ball));
    }

    // Left edge (bottom to top) — skip bottom and top corners
    for (float y = height - ballSize * 2; y >= ballSize; y -= ballSize)
    {
        auto ball = std::make_unique<Ball>(0.f);
        ball->objSprite->setPosition(sf::Vector2f(0.f, y));
        ball->velocity = sf::Vector2f(0.f, 0.f);
        ball->isCollidable = true;
        ball->isBorderBall = true;
        newObjects.emplace_back(std::move(ball));
    }
}

void Player::update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects)
{
    if (!hasSpawnedLayer)
    {
        spawnStartingLayer(newObjects);
        hasSpawnedLayer = true;
    }
    movement();

    spawnBall(newObjects, objects);

    checkGame(objects);

    // Merge newObjects into objects so they can collide
    for (auto& obj : newObjects) 
    {
        objects.push_back(std::move(obj));
    }
    newObjects.clear();
}
	
