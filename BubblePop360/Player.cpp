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
    if (!spacePressedLastFrame && isSpacePressed && noMovement)
    {
        shotCounter++;
        auto newBall = std::make_unique<Ball>(arrowRotation - 90);
        if (newBall->shootable)
        {
            for (auto& obj : newObjects)
            {
                if (!(obj->readyToJoinVector))
                    objects.push_back(std::move(obj));
            }
            objects[objects.size() - 1]->shoot(arrowRotation - 90);
            newObjects.emplace_back(std::move(newBall));
            newObjects[newObjects.size() - 1]->readyToJoinVector == false;
        }

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

void Player::spawnBorderBalls(float screenWidth, float screenHeight, float ballSize, std::vector<std::unique_ptr<Object>>& newObjects, std::vector<std::unique_ptr<Object>>& objects)
{
    float offset = borderLayerCount * ballSize;

    // Top and bottom edges
    for (float x = offset; x <= screenWidth - ballSize - offset; x += ballSize)
    {
        sf::Vector2f topPos(x, offset);
        if (isSpaceFree(topPos, ballSize, objects, newObjects))  
        {
            auto topBall = std::make_unique<Ball>(0.0f);
            topBall->objSprite->setPosition(topPos);
            topBall->isBorderBall = true;
            topBall->isCollidable = true;
            topBall->isPlayer = false;
            topBall->shootable = false;
            newObjects.push_back(std::move(topBall));
        }

        sf::Vector2f bottomPos(x, screenHeight - ballSize - offset);
        if (isSpaceFree(bottomPos, ballSize, objects, newObjects)) 
        {
            auto bottomBall = std::make_unique<Ball>(0.0f);
            bottomBall->objSprite->setPosition(bottomPos);
            bottomBall->isBorderBall = true;
            bottomBall->isCollidable = true;
            bottomBall->isPlayer = false;
            bottomBall->shootable = false;
            newObjects.push_back(std::move(bottomBall));
        }
    }

    // Left and right edges
    for (float y = offset + ballSize; y < screenHeight - ballSize - offset; y += ballSize)
    {
        sf::Vector2f leftPos(offset, y);
        if (isSpaceFree(leftPos, ballSize, objects, newObjects)) 
        {
            auto leftBall = std::make_unique<Ball>(0.0f);
            leftBall->objSprite->setPosition(leftPos);
            leftBall->isBorderBall = true;
            leftBall->isCollidable = true;
            leftBall->isPlayer = false;
            leftBall->shootable = false;
            newObjects.push_back(std::move(leftBall));
        }

        sf::Vector2f rightPos(screenWidth - ballSize - offset, y);
        if (isSpaceFree(rightPos, ballSize, objects, newObjects))  
        {
            auto rightBall = std::make_unique<Ball>(0.0f);
            rightBall->objSprite->setPosition(rightPos);
            rightBall->isBorderBall = true;
            rightBall->isCollidable = true;
            rightBall->isPlayer = false;
            rightBall->shootable = false;
            newObjects.push_back(std::move(rightBall));
        }
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
        ball->isPlayer = false;
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
        ball->isPlayer = false;
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
        ball->isPlayer = false;
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
        ball->isPlayer = false;
        newObjects.emplace_back(std::move(ball));
    }
}

bool Player::isSpaceFree(sf::Vector2f pos, float ballSize, const std::vector<std::unique_ptr<Object>>& objects, const std::vector<std::unique_ptr<Object>>& newObjects)
{
    float radiusSquared = ballSize * ballSize;

    auto checkList = [&](const std::vector<std::unique_ptr<Object>>& list) // lambda function, basically a function inside of a function
        {
        for (const auto& obj : list) 
        {
            if (!obj->objSprite) continue;
            sf::Vector2f otherPos = obj->objSprite->getPosition();
            float dx = otherPos.x - pos.x;
            float dy = otherPos.y - pos.y;
            float distanceSquared = dx * dx + dy * dy;
            if (distanceSquared < radiusSquared)
            {
                return false;
            }
        }
        return true;
        };

    return checkList(objects) && checkList(newObjects);
}

void Player::update(vector<std::unique_ptr<Object>>& newObjects, vector<std::unique_ptr<Object>>& objects)
{
    if (newObjects == objects)
    {
        checkGame(objects);
        return;
    }

    if (!hasSpawnedLayer)
    {
        spawnStartingLayer(newObjects);
        hasSpawnedLayer = true;
    }
    movement();

    if ((shotCounter >= 6) && noMovement)
    {
        this->borderLayerCount++;
        spawnBorderBalls(1024.0f, 768.0f, 64.0f, newObjects, objects);
        shotCounter = 0;
    }
   
    spawnBall(newObjects, objects);
  

    checkGame(objects);

    // Merge newObjects into objects so they can collide
    for (auto& obj : newObjects) 
    {
        objects.push_back(std::move(obj));
    }
    newObjects.clear();
}
	
