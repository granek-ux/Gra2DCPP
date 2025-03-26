#include "Interrupters.h"
#include "FileHandling.h"


auto Shop(sf::RenderWindow &window, Person &person) -> void {

    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return;
    }

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window.getSize()));


    sf::Color color = sf::Color::Black;
    color.a = 5;
    background.setFillColor(color);
    int counter = 0;

    auto armortext = std::string("Buy Armor");
    auto armorPricetext = std::string("Price: 50");

    auto armomShowedtext = sf::Text(sf::String(armortext), font, 18);

    auto armorPriceShowedtext = sf::Text(sf::String(armorPricetext), font, 18);

    auto armorButton = sf::RectangleShape(sf::Vector2f(300, 50));
    armorButton.setFillColor(sf::Color(107, 107, 102));

    armorButton.setPosition(100, 300);
    armomShowedtext.setPosition(200, 305);
    armorPriceShowedtext.setPosition(210, 325);


    auto regenerationtext = std::string("Buy Regeneration");
    auto regenerationPricetext = std::string("Price: 300");

    auto regenerationShowedtext = sf::Text(sf::String(regenerationtext), font, 18);

    auto regenerationPriceShowedtext = sf::Text(sf::String(regenerationPricetext), font, 18);

    auto regenerationButton = sf::RectangleShape(sf::Vector2f(300, 50));
    regenerationButton.setFillColor(sf::Color(107, 107, 102));

    regenerationButton.setPosition(500, 300);
    regenerationShowedtext.setPosition(590, 305);
    regenerationPriceShowedtext.setPosition(610, 325);


    auto fastertext = std::string("Buy Faster Movment");
    auto fasterPricetext = std::string("Price: 250");

    auto fasterShowedtext = sf::Text(sf::String(fastertext), font, 18);

    auto fasterPriceShowedtext = sf::Text(sf::String(fasterPricetext), font, 18);

    auto fasterButton = sf::RectangleShape(sf::Vector2f(300, 50));
    fasterButton.setFillColor(sf::Color(107, 107, 102));

    fasterButton.setPosition(900, 300);
    fasterShowedtext.setPosition(980, 305);
    fasterPriceShowedtext.setPosition(1010, 325);


    auto exittext = std::string("Exit");

    auto exitShowedtexet = sf::Text(sf::String(exittext), font, 25);

    auto exitButton = sf::RectangleShape(sf::Vector2f(300, 50));
    exitButton.setFillColor(sf::Color(209, 59, 59));

    exitButton.setPosition(500, 500);
    exitShowedtexet.setPosition(625, 515);


    bool isCliced = false;

    while (!isCliced) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isCliced = true;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    if (exitButton.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        isCliced = true;
                    }
                    if (armorButton.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        if (person.money >= 50) {
                            person.money -= 50;
                            person.armor += 3;
                        }
                    }
                    if (regenerationButton.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        if (!person.regeneration) {
                            if (person.money >= 300) {
                                person.money -= 300;
                                person.regeneration = true;
                            }
                        }
                    }
                    if (fasterButton.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        if (person.money >= 250) {
                            person.money -= 250;
                            person.velocity.x *= 1.5;
                            person.velocity.y *= 1.5;
                            person.counterhowfast++;
                        }
                    }

                }
            }
        }

        if (counter < 100) {
            window.draw(background);

            window.draw(armorButton);
            window.draw(armomShowedtext);
            window.draw(armorPriceShowedtext);
            if (!person.regeneration) {
                window.draw(regenerationButton);
                window.draw(regenerationShowedtext);
                window.draw(regenerationPriceShowedtext);
            }
            window.draw(fasterButton);
            window.draw(fasterShowedtext);
            window.draw(fasterPriceShowedtext);

            window.draw(exitButton);
            window.draw(exitShowedtexet);


            window.display();
            counter++;
        }
    }
}


auto pauseBetweenLevels(sf::RenderWindow &window, Person &person, Level &level) -> void {

    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return;
    }

    auto buttonContiniue = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonContiniue.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 200});
    buttonContiniue.setFillColor(sf::Color::Magenta);

    auto buttonContiniuetext = std::string("Continiue");
    auto buttonContiniuetexttext = sf::Text(sf::String(buttonContiniuetext), font, 24);
    buttonContiniuetexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 40, 210});

    auto buttonLoad = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonLoad.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 300});
    buttonLoad.setFillColor(sf::Color::Magenta);

    auto buttonLoadtext = std::string("Load");
    auto buttonLoadtexttext = sf::Text(sf::String(buttonLoadtext), font, 24);
    buttonLoadtexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 20, 310});

    auto buttonSave = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonSave.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 400});
    buttonSave.setFillColor(sf::Color::Green);

    auto buttonSavetext = std::string("Save");
    auto buttonSavetexttext = sf::Text(sf::String(buttonSavetext), font, 24);
    buttonSavetexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 20, 410});


    auto buttonExit = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonExit.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 500});
    buttonExit.setFillColor(sf::Color::Red);

    auto buttonExitText = std::string("Exit");
    auto buttonExitTextText = sf::Text(sf::String(buttonExitText), font, 24);
    buttonExitTextText.setPosition({static_cast<float>(window.getSize().x) / 2 - 20, 510});


    bool notClicked = true;

    while (notClicked) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                notClicked = false;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    if (buttonContiniue.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        notClicked = false;

                    }
                    if (buttonSave.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        Saving(person, level);

                    }
                    if (buttonLoad.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        Load(window, person, level);
                        notClicked = false;

                    }
                    if (buttonExit.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        window.close();
                        return;
                    }
                }
            }

            window.clear();
            window.draw(buttonContiniue);
            window.draw(buttonLoad);
            window.draw(buttonSave);
            window.draw(buttonExit);
            window.draw(buttonContiniuetexttext);
            window.draw(buttonLoadtexttext);
            window.draw(buttonSavetexttext);
            window.draw(buttonExitTextText);
            window.display();
        }
    }
}

auto endGame(sf::RenderWindow &window, Person &person, Level &level) -> void {
    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return;
    }

    auto text = sf::Text("Game Over", font, 45);
    text.setPosition({static_cast<float>(window.getSize().x) / 2 - 120, 50});
    text.setFillColor(sf::Color::Red);

    auto buttonPlay = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonPlay.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 200});
    buttonPlay.setFillColor(sf::Color::Magenta);

    auto buttonPlaytext = std::string("New Game");
    auto buttonPlaytexttext = sf::Text(sf::String(buttonPlaytext), font, 24);
    buttonPlaytexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 60, 210});


    auto buttonLoad = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonLoad.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 400});
    buttonLoad.setFillColor(sf::Color::Green);

    auto buttonLoadtext = std::string("Load");
    auto buttonLoadtexttext = sf::Text(sf::String(buttonLoadtext), font, 24);
    buttonLoadtexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 50, 410});


    auto buttonExit = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonExit.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 600});
    buttonExit.setFillColor(sf::Color::Red);

    auto buttonText = std::string("EXIT");
    auto buttonTextText = sf::Text(sf::String(buttonText), font, 24);
    buttonTextText.setPosition({static_cast<float>(window.getSize().x) / 2 - 50, 610});

    bool isCliced = false;
    while (!isCliced) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    if (buttonExit.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        window.close();
                        isCliced = true;
                        return;
                    }
                    if (buttonPlay.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        person = Person{sf::Vector2f(100, 100), 3};
                        if (!person.texture.loadFromFile("../Frog Heaven - assets/Frog.png")) {
                            fmt::println("error while loading image ");
                            return;
                        }
                        person.imagine = sf::Sprite(person.texture);
                        level.NewLevel(window, person);
                        isCliced = true;
                    }
                    if (buttonLoad.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        Load(window, person, level);
                        isCliced = true;
                    }
                }
            }
        }

        window.clear();
        window.draw(text);
        window.draw(buttonPlay);
        window.draw(buttonPlaytexttext);
        window.draw(buttonExit);
        window.draw(buttonLoad);
        window.draw(buttonTextText);
        window.draw(buttonLoadtexttext);
        window.display();
    }
}

auto ShowInfo(sf::RenderWindow &window, Person const &person) -> void {
    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return;
    }

    auto HeathText = std::string(
            "Healt: " + std::to_string(person.Helth) + " Armor: " + std::to_string(person.armor) + " Money: " +
            std::to_string(person.money) + " Level: " + std::to_string(person.currentLevel));
    auto HealthShowedText = sf::Text(sf::String(HeathText), font, 15);
    HealthShowedText.setPosition({0, 0});
    HealthShowedText.setFillColor(sf::Color::White);


    auto BonusText = std::string("number of bombs: " + std::to_string(person.numberOfBombs) + " number of freeze: " +
                                 std::to_string(person.numberOfFreeze));
    auto BonusShowedText = sf::Text(sf::String(BonusText), font, 15);
    BonusShowedText.setPosition({0, 20});
    BonusShowedText.setFillColor(sf::Color::White);


    window.draw(HealthShowedText);
    window.draw(BonusShowedText);
}


auto Pauza(sf::RenderWindow &window, Person &person, Level &level) -> void {
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window.getSize()));

    sf::Color color = sf::Color::Black;
    color.a = 5;
    background.setFillColor(color);
    int counter = 0;

    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return;
    }

    auto buttonPlay = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonPlay.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 200});
    buttonPlay.setFillColor(sf::Color::Magenta);

    auto buttonPlaytext = std::string("PLAY");
    auto buttonPlaytexttext = sf::Text(sf::String(buttonPlaytext), font, 24);
    buttonPlaytexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 20, 210});


    auto buttonLoad = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonLoad.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 300});
    buttonLoad.setFillColor(sf::Color::Magenta);

    auto buttonLoadtext = std::string("Load");
    auto buttonLoadtexttext = sf::Text(sf::String(buttonLoadtext), font, 24);
    buttonLoadtexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 20, 310});


    auto buttonExit = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonExit.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 400});
    buttonExit.setFillColor(sf::Color::Magenta);

    auto buttonExitText = std::string("Exit");
    auto buttonExitTextText = sf::Text(sf::String(buttonExitText), font, 24);
    buttonExitTextText.setPosition({static_cast<float>(window.getSize().x) / 2 - 20, 410});


    bool notClicked = true;
    while (notClicked) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                notClicked = false;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    if (buttonPlay.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        notClicked = false;
                    }
                    if (buttonLoad.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        Load(window, person, level);
                        notClicked = false;
                    }
                    if (buttonExit.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        window.close();
                        return;
                    }
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                    notClicked = false;
                }
            }
        }
        if (counter < 100) {
            window.draw(background);
            window.draw(buttonPlay);
            window.draw(buttonPlaytexttext);
            window.draw(buttonExit);
            window.draw(buttonExitTextText);
            window.draw(buttonLoad);
            window.draw(buttonLoadtexttext);
            window.display();
            counter++;
        }
    }
}