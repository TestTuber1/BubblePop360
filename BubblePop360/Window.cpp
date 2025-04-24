#include "Window.hpp"

void Window::run()
{
    int i = 0;
    sf::Music music("../assets/song.ogg");
    music.setLoopPoints({ sf::seconds(0), sf::seconds(4.35) });
    music.setLooping(true);
    music.play();

    Ball::loadTextures();
    double points = 0.0;

    sf::Font font;
    if (!font.openFromFile("../assets/KronaOne-Regular.ttf"))
    {
    }
    string something = "";
    unsigned int characterSize = 42;
    sf::Text pointsDisplay(font, something, characterSize);
    pointsDisplay.setFont(font);
    pointsDisplay.setCharacterSize(characterSize);
    sf::Color pointsColor(30, 30, 36);
    pointsDisplay.setFillColor(pointsColor);

    sf::Text finalScore(font, "Final Score", 52);
    finalScore.setFillColor(pointsColor);
    finalScore.setPosition(sf::Vector2f(325.f, 250.f));

    vector<std::unique_ptr<Object>> objects;
    objects.push_back(std::make_unique<Player>());
    objects.push_back(std::make_unique<Ball>(1.f));

    Screen currentScreen = Screen::Menu;
    sf::RenderWindow window(sf::VideoMode({ 1024, 768 }), "", sf::Style::Close);
    sf::Color background(252, 247, 255);
    window.setFramerateLimit(60);

    sf::FloatRect bounds = pointsDisplay.getLocalBounds();
    float containerWidth = window.getSize().x;
    float offset = (containerWidth - bounds.size.x) / 2.0f;

    sf::Texture titleTexture;
    titleTexture.loadFromFile("../assets/title.png");

    sf::Sprite title(titleTexture);

    float xtitleScale = 0.333, ytitleScale = 0.333;
    sf::Vector2f titleScale(xtitleScale, ytitleScale);
    title.scale(titleScale);

    float xTitlePos = 265, yTitlePos = -25;
    sf::Vector2f titlePos(xTitlePos, yTitlePos);
    title.move(titlePos);

    sf::Texture instructionTexture;
    instructionTexture.loadFromFile("../assets/instructions.png");

    sf::Sprite instructions(instructionTexture);

    float xinstructionScale = 0.25, yinstructionScale = 0.25;
    sf::Vector2f instructionScale(xinstructionScale, yinstructionScale);
    instructions.scale(instructionScale);

    float xInstructionPos = 0, yInstructionPos = -5;
    sf::Vector2f instructionPos(xInstructionPos, yInstructionPos);
    instructions.move(instructionPos);

    sf::Texture programmersTexture;
    programmersTexture.loadFromFile("../assets/programmers.png");

    sf::Sprite programmers(programmersTexture);

    float xProgrammersScale = 0.25, yProgrammersScale = 0.25;
    sf::Vector2f programmersScale(xProgrammersScale, yProgrammersScale);
    programmers.scale(programmersScale);

    float xProgrammersPos = 0, yProgrammersPos = -5;
    sf::Vector2f programmersPos(xProgrammersPos, yProgrammersPos);
    programmers.move(programmersPos);

    // -------------------------------------------------------------------------

    sf::Texture playTexture;
    playTexture.loadFromFile("../assets/play.png");

    sf::Sprite playButton(playTexture);

    float xButtonScale = 0.333, yButtonScale = 0.333;
    sf::Vector2f buttonScale(xButtonScale, yButtonScale);
    playButton.scale(buttonScale);

    float xPlayPos = 402, yPlayPos = 475;
    sf::Vector2f playPos(xPlayPos, yPlayPos);
    playButton.move(playPos);

    // -------------------------------------------------------------------------

    sf::Texture guideTexture;
    guideTexture.loadFromFile("../assets/guide.png");

    sf::Sprite guideButton(guideTexture);

    guideButton.scale(buttonScale);

    float xGuidePos = 146, yGuidePos = 550;
    sf::Vector2f guidePos(xGuidePos, yGuidePos);
    guideButton.move(guidePos);

    // -------------------------------------------------------------------------

    sf::Texture creditsTexture;
    creditsTexture.loadFromFile("../assets/credits.png");

    sf::Sprite creditsButton(creditsTexture);

    creditsButton.scale(buttonScale);

    float xCreditsPos = 658, yCreditsPos = 550;
    sf::Vector2f creditsPos(xCreditsPos, yCreditsPos);
    creditsButton.move(creditsPos);

    // -------------------------------------------------------------------------

    sf::Texture redMenuTexture;
    redMenuTexture.loadFromFile("../assets/redMenu.png");

    sf::Sprite redMenuButton(redMenuTexture);

    redMenuButton.scale(buttonScale);

    float xRedMenuPos = 402, yRedMenuPos = 600;
    sf::Vector2f redMenuPos(xRedMenuPos, yRedMenuPos);
    redMenuButton.move(redMenuPos);

    // -------------------------------------------------------------------------

    sf::Texture blueMenuTexture;
    blueMenuTexture.loadFromFile("../assets/blueMenu.png");

    sf::Sprite blueMenuButton(blueMenuTexture);

    blueMenuButton.scale(buttonScale);

    float xBlueMenuPos = 402, yBlueMenuPos = 600;
    sf::Vector2f blueMenuPos(xBlueMenuPos, yBlueMenuPos);
    blueMenuButton.move(blueMenuPos);

    // -------------------------------------------------------------------------

    sf::Texture yellowMenuTexture;
    yellowMenuTexture.loadFromFile("../assets/yellowMenu.png");

    sf::Sprite yellowMenuButton(yellowMenuTexture);

    yellowMenuButton.scale(buttonScale);

    float xYellowMenuPos = 402, yYellowMenuPos = 600;
    sf::Vector2f yellowMenuPos(xYellowMenuPos, yYellowMenuPos);
    yellowMenuButton.move(yellowMenuPos);

    // -------------------------------------------------------------------------

    float playRotation = 0.0;
    AnimationPhase playPhase = AnimationPhase::None;
    bool wasPlayHovered = false;

    float guideRotation = 0.0;
    AnimationPhase guidePhase = AnimationPhase::None;
    bool wasGuideHovered = false;

    float creditsRotation = 0.0;
    AnimationPhase creditsPhase = AnimationPhase::None;
    bool wasCreditsHovered = false;

    float redMenuRotation = 0.0;
    AnimationPhase redMenuPhase = AnimationPhase::None;
    bool wasRedMenuHovered = false;

    float blueMenuRotation = 0.0;
    AnimationPhase blueMenuPhase = AnimationPhase::None;
    bool wasBlueMenuHovered = false;

    float yellowMenuRotation = 0.0;
    AnimationPhase yellowMenuPhase = AnimationPhase::None;
    bool wasYellowMenuHovered = false;

    bool playclicked = false;
    bool guideclicked = false;
    bool creditsclicked = false;

    bool redmenuclicked = false;
    bool bluemenuclicked = false;
    bool yellowmenuclicked = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);

        // -------------------------------------------------------------------------

        bool isPlayHovered = playButton.getGlobalBounds().contains(mouseWorld);
        if (isPlayHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            playclicked = true;
        }

        if (isPlayHovered && !wasPlayHovered && playPhase == AnimationPhase::None) {
            playPhase = AnimationPhase::RotateForward;
        }
        wasPlayHovered = isPlayHovered;

        // -------------------------------------------------------------------------

        bool isGuideHovered = guideButton.getGlobalBounds().contains(mouseWorld);
        if (isGuideHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            guideclicked = true;
        }

        if (isGuideHovered && !wasGuideHovered && guidePhase == AnimationPhase::None) {
            guidePhase = AnimationPhase::RotateForward;
        }
        wasGuideHovered = isGuideHovered;

        // -------------------------------------------------------------------------


        bool isCreditsHovered = creditsButton.getGlobalBounds().contains(mouseWorld);
        if (isCreditsHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            creditsclicked = true;
        }

        if (isCreditsHovered && !wasCreditsHovered && creditsPhase == AnimationPhase::None) {
            creditsPhase = AnimationPhase::RotateForward;
        }
        wasCreditsHovered = isCreditsHovered;

        // -------------------------------------------------------------------------

        bool isRedMenuHovered = redMenuButton.getGlobalBounds().contains(mouseWorld);
        if (isRedMenuHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            redmenuclicked = true;
        }

        if (isRedMenuHovered && !wasRedMenuHovered && redMenuPhase == AnimationPhase::None) {
            redMenuPhase = AnimationPhase::RotateForward;
        }
        wasRedMenuHovered = isRedMenuHovered;

        // -------------------------------------------------------------------------

        bool isBlueMenuHovered = blueMenuButton.getGlobalBounds().contains(mouseWorld);
        if (isBlueMenuHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            bluemenuclicked = true;
        }

        if (isBlueMenuHovered && !wasBlueMenuHovered && blueMenuPhase == AnimationPhase::None) {
            blueMenuPhase = AnimationPhase::RotateForward;
        }
        wasBlueMenuHovered = isBlueMenuHovered;

        // -------------------------------------------------------------------------

        bool isYellowMenuHovered = yellowMenuButton.getGlobalBounds().contains(mouseWorld);
        if (isYellowMenuHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            yellowmenuclicked = true;
        }

        if (isYellowMenuHovered && !wasYellowMenuHovered && yellowMenuPhase == AnimationPhase::None) {
            yellowMenuPhase = AnimationPhase::RotateForward;
        }
        wasYellowMenuHovered = isYellowMenuHovered;

        // -------------------------------------------------------------------------

        float rotationSpeed = 0.56;
        
        // -------------------------------------------------------------------------

        switch (playPhase) {
        case AnimationPhase::RotateForward:
            playRotation += rotationSpeed;
            if (playRotation >= 1.0) {
                playRotation = 1.0;
                playPhase = AnimationPhase::RotateBackward;
            }
            break;
        case AnimationPhase::RotateBackward:
            playRotation -= rotationSpeed;
            if (playRotation <= -2.0) {
                playRotation = -2.0;
                playPhase = AnimationPhase::ReturnToCenter;
            }
            break;
        case AnimationPhase::ReturnToCenter:
            playRotation += rotationSpeed;
            if (playRotation >= 0.0) {
                playRotation = 0.0;
                playPhase = AnimationPhase::None;
            }
            break;
        default: break;
        }
        playButton.setRotation(sf::degrees(playRotation));

        // -------------------------------------------------------------------------

        switch (guidePhase) {
        case AnimationPhase::RotateForward:
            guideRotation += rotationSpeed;
            if (guideRotation >= 1.0) {
                guideRotation = 1.0;
                guidePhase = AnimationPhase::RotateBackward;
            }
            break;
        case AnimationPhase::RotateBackward:
            guideRotation -= rotationSpeed;
            if (guideRotation <= -2.0) {
                guideRotation = -2.0;
                guidePhase = AnimationPhase::ReturnToCenter;
            }
            break;
        case AnimationPhase::ReturnToCenter:
            guideRotation += rotationSpeed;
            if (guideRotation >= 0.0) {
                guideRotation = 0.0;
                guidePhase = AnimationPhase::None;
            }
            break;
        default: break;
        }
        guideButton.setRotation(sf::degrees(guideRotation));

        // -------------------------------------------------------------------------

        switch (creditsPhase) {
        case AnimationPhase::RotateForward:
            creditsRotation += rotationSpeed;
            if (creditsRotation >= 1.0) {
                creditsRotation = 1.0;
                creditsPhase = AnimationPhase::RotateBackward;
            }
            break;
        case AnimationPhase::RotateBackward:
            creditsRotation -= rotationSpeed;
            if (creditsRotation <= -2.0) {
                creditsRotation = -2.0;
                creditsPhase = AnimationPhase::ReturnToCenter;
            }
            break;
        case AnimationPhase::ReturnToCenter:
            creditsRotation += rotationSpeed;
            if (creditsRotation >= 0.0) {
                creditsRotation = 0.0;
                creditsPhase = AnimationPhase::None;
            }
            break;
        default: break;
        }
        creditsButton.setRotation(sf::degrees(creditsRotation));

        // -------------------------------------------------------------------------

        switch (redMenuPhase) {
        case AnimationPhase::RotateForward:
            redMenuRotation += rotationSpeed;
            if (redMenuRotation >= 1.0) {
                redMenuRotation = 1.0;
                redMenuPhase = AnimationPhase::RotateBackward;
            }
            break;
        case AnimationPhase::RotateBackward:
            redMenuRotation -= rotationSpeed;
            if (redMenuRotation <= -2.0) {
                redMenuRotation = -2.0;
                redMenuPhase = AnimationPhase::ReturnToCenter;
            }
            break;
        case AnimationPhase::ReturnToCenter:
            redMenuRotation += rotationSpeed;
            if (redMenuRotation >= 0.0) {
                redMenuRotation = 0.0;
                redMenuPhase = AnimationPhase::None;
            }
            break;
        default: break;
        }
        redMenuButton.setRotation(sf::degrees(redMenuRotation));

        // -------------------------------------------------------------------------

        switch (blueMenuPhase) {
        case AnimationPhase::RotateForward:
            blueMenuRotation += rotationSpeed;
            if (blueMenuRotation >= 1.0) {
                blueMenuRotation = 1.0;
                blueMenuPhase = AnimationPhase::RotateBackward;
            }
            break;
        case AnimationPhase::RotateBackward:
            blueMenuRotation -= rotationSpeed;
            if (blueMenuRotation <= -2.0) {
                blueMenuRotation = -2.0;
                blueMenuPhase = AnimationPhase::ReturnToCenter;
            }
            break;
        case AnimationPhase::ReturnToCenter:
            blueMenuRotation += rotationSpeed;
            if (blueMenuRotation >= 0.0) {
                blueMenuRotation = 0.0;
                blueMenuPhase = AnimationPhase::None;
            }
            break;
        default: break;
        }
        blueMenuButton.setRotation(sf::degrees(blueMenuRotation));

        // -------------------------------------------------------------------------

        switch (yellowMenuPhase) {
        case AnimationPhase::RotateForward:
            yellowMenuRotation += rotationSpeed;
            if (yellowMenuRotation >= 1.0) {
                yellowMenuRotation = 1.0;
                yellowMenuPhase = AnimationPhase::RotateBackward;
            }
            break;
        case AnimationPhase::RotateBackward:
            yellowMenuRotation -= rotationSpeed;
            if (yellowMenuRotation <= -2.0) {
                yellowMenuRotation = -2.0;
                yellowMenuPhase = AnimationPhase::ReturnToCenter;
            }
            break;
        case AnimationPhase::ReturnToCenter:
            yellowMenuRotation += rotationSpeed;
            if (yellowMenuRotation >= 0.0) {
                yellowMenuRotation = 0.0;
                yellowMenuPhase = AnimationPhase::None;
            }
            break;
        default: break;
        }
        yellowMenuButton.setRotation(sf::degrees(yellowMenuRotation));

        // -------------------------------------------------------------------------

        window.clear(background);

        switch (currentScreen)
        {
        case Screen::Menu:
            window.draw(title);

            window.draw(playButton);
            window.draw(guideButton);
            window.draw(creditsButton);
            break;
        case Screen::Play:
            i = 0;
            music.stop();
            while (objects[0]->state == gameState::Running)
            {
                window.clear(background);
                std::vector<std::unique_ptr<Object>> newObjects;
                for (size_t i = 0; i < objects.size(); ++i)
                {
                    objects[i]->update(newObjects, objects);
                }
                for (auto& obj : newObjects)
                {
                    objects.push_back(std::move(obj));
                }
                for (size_t i = 0; i < objects.size(); ++i)
                {
                    if (objects[i]->objSprite)
                        window.draw(*(objects[i]->objSprite));
                }
                pointsDisplay.setString(std::to_string((int)(objects[0]->points)));
                points = objects[0]->points;
                bounds = pointsDisplay.getLocalBounds();
                containerWidth = window.getSize().x;
                offset = (containerWidth - bounds.size.x) / 2.0f;
                pointsDisplay.setPosition(sf::Vector2f(offset, 1.f));
                window.draw(pointsDisplay);
                while (const std::optional event = window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                        window.close();
                }
                window.display();
            }
            currentScreen = Screen::GameOver;
            break;
        case Screen::Guide:
            window.draw(instructions);
            window.draw(blueMenuButton);
            break;
        case Screen::Credits:
            window.draw(programmers);
            window.draw(yellowMenuButton); 
            break;
        case Screen::GameOver:
            if (i == 0)
                music.play();
            window.draw(finalScore);
            pointsDisplay.setPosition(sf::Vector2f(offset, 340.f));
            pointsDisplay.setString(std::to_string((int)(points)));
            window.draw(pointsDisplay);
            window.draw(redMenuButton);
            objects.clear();
            objects.push_back(std::make_unique<Player>());
            objects.push_back(std::make_unique<Ball>(1.f));
            i++;
            break;
        }
        
        window.display();

        if (playclicked) {
            currentScreen = Screen::Play;
            playclicked = false;
        }
        if (guideclicked) 
        {
            currentScreen = Screen::Guide;
            guideclicked = false;
        }
        if (creditsclicked) 
        {
            currentScreen = Screen::Credits;
            creditsclicked = false;
        }
        if (redmenuclicked || bluemenuclicked || yellowmenuclicked)
        {
            currentScreen = Screen::Menu;
            redmenuclicked = false;
            bluemenuclicked = false;
            yellowmenuclicked = false;
        }
    }
}
