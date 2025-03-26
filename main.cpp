#include "SFML/Graphics.hpp"
#include "fmt/core.h"
#include "Entity.h"
#include "FileHandling.h"
#include "Interrupters.h"

auto Menu() -> void;

auto Game(sf::RenderWindow &window, Person &person, Level &level) -> void;

auto main() -> int {
    Menu();
}

auto Menu() -> void {

    auto window = sf::RenderWindow(sf::VideoMode(1920, 1080), "Frog Heaven", sf::Style::Fullscreen);
        auto texture = sf::Texture();

    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return;
    }
    auto text = sf::Text("FROG HAVEN", font, 45);
    text.setPosition({static_cast<float>(window.getSize().x) / 2 - 120, 50});

    auto buttonPlay = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonPlay.setPosition({static_cast<float>(window.getSize().x) / 2 - 150, 200});
    buttonPlay.setFillColor(sf::Color::Magenta);

    auto buttonPlaytext = std::string("PLAY");
    auto buttonPlaytexttext = sf::Text(sf::String(buttonPlaytext), font, 24);
    buttonPlaytexttext.setPosition({static_cast<float>(window.getSize().x) / 2 - 50, 210});


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


    while (window.isOpen()) {
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
                        return;
                    }
                    if (buttonPlay.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        Person p = Person{sf::Vector2f(100, 100), 3};
                        Level l = Level(window, p);
                        Game(window, p,l);

                    }
                    if (buttonLoad.getGlobalBounds().contains(
                            {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        Person p = Person(sf::Vector2f(100, 100), 3);
                        Level l = Level(window, p);
                        Load(window, p, l);
                        Game(window, p,l);
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

auto Game(sf::RenderWindow &window, Person &person, Level &levels) -> void {
    if (!person.texture.loadFromFile("../Frog Heaven - assets/Frog.png")) {
        fmt::println("error while loading image ");
        return;
    }
    person.imagine = sf::Sprite(person.texture);
    while (window.isOpen()) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    if (person.CanShoot())
                        levels.maps[person.currentPoint.x][person.currentPoint.y].bullets.push_back(person.Shot());
                }
                if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                    Pauza(window, person, levels);
                }
                if (event.key.scancode == sf::Keyboard::Scan::Q) {
                    if (person.numberOfBombs > 0) {
                        Destruction(levels.maps[person.currentPoint.x][person.currentPoint.y].obstacles, person,
                                    window);
                        person.numberOfBombs--;
                    }
                }
                if (event.key.scancode == sf::Keyboard::Scan::B) {
                    Shop(window, person);
                }
                if (event.key.scancode == sf::Keyboard::Scan::F) {
                    if (person.numberOfFreeze > 0) {
                        person.numberOfFreeze--;
                        levels.freezetime.clock.restart();
                        levels.freeze = true;
                    }
                }
            }
        }
        Movment(person, window, levels.maps[person.currentPoint.x][person.currentPoint.y].obstacles);
        person.SetPosition();
        person.Regeneratiom();

        CanSpawnBonus(window, person, levels);

        if (person.Helth < 0) endGame(window, person, levels);


        window.clear();

        auto usedBullets = std::vector<int>();

        window.draw(person.imagine);
        Drawing(window, levels.maps[person.currentPoint.x][person.currentPoint.y].obstacles);

        for (Enemy &enemy: levels.maps[person.currentPoint.x][person.currentPoint.y].enemys) {
            if (Freeze(levels))
                ShootByEnemy(person, enemy, levels.maps[person.currentPoint.x][person.currentPoint.y].bullets);
            MoveEnemy(enemy, window, levels.maps[person.currentPoint.x][person.currentPoint.y], person);

            if (enemy.Helth == 0) {
                if (enemy.czyIstnieje) {
                    switch (enemy.typeOfEnemy) {
                        case normal:
                            person.money += 20;
                            break;
                        case lightning:
                            person.money += 30;
                            break;
                        case leviathan:
                            person.money += 50;
                            break;
                    }
                }
                enemy.czyIstnieje = false;
            }
            if (enemy.czyIstnieje) window.draw(enemy.shape);
        }

        int i = 0;
        for (Bullet &bullet: levels.maps[person.currentPoint.x][person.currentPoint.y].bullets) {
            bullet.position += bullet.velocity;
            bullet.shape.setPosition(bullet.position);
            window.draw(bullet.shape);
            if (!IsInBound(bullet, window) ||
                IsHIT(bullet, person, levels.maps[person.currentPoint.x][person.currentPoint.y].enemys,
                      levels.maps[person.currentPoint.x][person.currentPoint.y].obstacles))
                usedBullets.push_back(i);
            i++;
        }
        Erasebullets(levels.maps[person.currentPoint.x][person.currentPoint.y].bullets, usedBullets);

        for (int i = 0; i < levels.maps[person.currentPoint.x][person.currentPoint.y].bonuses.size(); i++) {
            levels.maps[person.currentPoint.x][person.currentPoint.y].bonuses[i]->IsTouched(person);

            if (!levels.maps[person.currentPoint.x][person.currentPoint.y].bonuses[i]->touhced)
                window.draw(levels.maps[person.currentPoint.x][person.currentPoint.y].bonuses[i]->shape);
        }

        if (!IsEnemysAlive(levels.maps[person.currentPoint.x][person.currentPoint.y].enemys)) {
            Drawing(window, levels.maps[person.currentPoint.x][person.currentPoint.y].exits);
            Exit(person, window, levels.maps);
        }
        ShowInfo(window, person);


        window.display();
        if (levels.NoumberOfMaps == person.numberofMpasPassed) {
            pauseBetweenLevels(window, person, levels);
            levels.NewLevel(window, person);
        }
    }

}