#include "Window.hpp"

void Window::run()
{
    sf::RenderWindow window(sf::VideoMode({ 1024, 768 }), "", sf::Style::Close);
    sf::Color background(252, 247, 255);
    window.setFramerateLimit(60);

    sf::Texture titleTexture;
    titleTexture.loadFromFile("../assets/title.png");

    sf::Sprite title(titleTexture);

    float xtitleScale = 0.333, ytitleScale = 0.333;
    sf::Vector2f titleScale(xtitleScale, ytitleScale);
    title.scale(titleScale);

    float xTitlePos = 265, yTitlePos = -25;
    sf::Vector2f titlePos(xTitlePos, yTitlePos);
    title.move(titlePos);

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

    float playRotation = 0.0;
    AnimationPhase playPhase = AnimationPhase::None;
    bool wasPlayHovered = false;

    float guideRotation = 0.0;
    AnimationPhase guidePhase = AnimationPhase::None;
    bool wasGuideHovered = false;

    float creditsRotation = 0.0;
    AnimationPhase creditsPhase = AnimationPhase::None;
    bool wasCreditsHovered = false;

    bool playclicked = false;
    bool guideclicked = false;
    bool creditsclicked = false;

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
            window.close();
        }

        if (isPlayHovered && !wasPlayHovered && playPhase == AnimationPhase::None) {
            playPhase = AnimationPhase::RotateForward;
        }
        wasPlayHovered = isPlayHovered;

        // -------------------------------------------------------------------------

        bool isGuideHovered = guideButton.getGlobalBounds().contains(mouseWorld);
        if (isGuideHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            guideclicked = true;
            window.close();
        }

        if (isGuideHovered && !wasGuideHovered && guidePhase == AnimationPhase::None) {
            guidePhase = AnimationPhase::RotateForward;
        }
        wasGuideHovered = isGuideHovered;

        // -------------------------------------------------------------------------


        bool isCreditsHovered = creditsButton.getGlobalBounds().contains(mouseWorld);
        if (isCreditsHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            creditsclicked = true;
            window.close();
        }

        if (isCreditsHovered && !wasCreditsHovered && creditsPhase == AnimationPhase::None) {
            creditsPhase = AnimationPhase::RotateForward;
        }
        wasCreditsHovered = isCreditsHovered;

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

        window.clear(background);

        window.draw(title);

        window.draw(playButton);
        window.draw(guideButton);
        window.draw(creditsButton);

        window.display();
    }


    if (playclicked) {
        sf::RenderWindow playwindow(sf::VideoMode({ 1024, 768 }), "", sf::Style::Close);
        sf::Color background(255, 200, 255);
        window.setFramerateLimit(60);
        sf::Texture arrowTexture;
        arrowTexture.loadFromFile("../assets/arrow.png");

        sf::Sprite arrow(arrowTexture);

        arrow.setScale(sf::Vector2f(0.1f, 0.1f));

        arrow.setOrigin(sf::Vector2f(arrowTexture.getSize().x * 0.5, arrowTexture.getSize().y * 1));

        arrow.setPosition(sf::Vector2f(514.f, 384.f));

        float arrowRotation = 0.0;
        float rotationSpeed = .07;
        AnimationPhase arrowPhase = AnimationPhase::None;
        bool wasRightPressed = false;
        while (playwindow.isOpen()) {
            while (const std::optional event = playwindow.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    playwindow.close();
            }
            bool isRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right);
             if (isRightPressed)  {
                 arrowRotation += rotationSpeed;
                    std::cout << "sdsd";
                }
             bool isLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left);
             if (isLeftPressed) {
                 arrowRotation -= rotationSpeed;
             }
            wasRightPressed = isRightPressed;
            

            arrow.setRotation(sf::degrees(arrowRotation));
            playwindow.clear(background);
            playwindow.draw(arrow);
            playwindow.display();
        }
    }
    if (guideclicked) {
        sf::RenderWindow guidewindow(sf::VideoMode({ 1024, 768 }), "", sf::Style::Close);
        while (guidewindow.isOpen()) {
            while (const std::optional event = guidewindow.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    guidewindow.close();
            }

            guidewindow.clear(background);
            guidewindow.display();
        }
    }
    if (creditsclicked) {
        sf::RenderWindow creditswindow(sf::VideoMode({ 1024, 768 }), "", sf::Style::Close);
        while (creditswindow.isOpen()) {
            while (const std::optional event = creditswindow.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    creditswindow.close();
            }

            creditswindow.clear(background);
            creditswindow.display();
        }
    }
}
