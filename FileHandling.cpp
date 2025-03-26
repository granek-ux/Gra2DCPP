#include "FileHandling.h"
#include "fmt/core.h"

auto placeToWrite() -> std::string {
    sf::RenderWindow window(sf::VideoMode(400, 300), "Give name file", sf::Style::Default);
    auto font = sf::Font();
    if (!font.loadFromFile("../Frog Heaven - assets/BrownieStencil-8O8MJ.ttf")) {
        fmt::println("Failed to load font.");
        return "";
    }
    sf::String playerInput;
    sf::Text playerText;
    playerText.setPosition(50, 100);
    playerText.setFont(font);

    while (window.isOpen()) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 123 && event.text.unicode > 48) {
                    playerInput += event.text.unicode;
                    playerText.setString(playerInput);
                }
                if (event.text.unicode == 8) {
                    if (!playerInput.isEmpty()) {
                        playerInput = delatelast(playerInput);
                        playerText.setString(playerInput);
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Enter) {
                    window.close();
                }
            }
        }
        window.clear();
        window.draw(playerText);
        window.display();
    }

    return playerInput;
}

auto delatelast(sf::String str) -> sf::String {
    std::string oldStr = str;
    std::string newStr = "";

    for (int i = 0; i < oldStr.size() - 1; i++)
        newStr += oldStr[i];
    auto goodText = sf::String(newStr);
    return goodText;
}

auto Saving(Person const &person, Level const &level) -> void {
    auto info = std::vector<int>();
    info.push_back(level.numberOfLevel);
    info.push_back(person.Helth);
    info.push_back(person.numberOfBombs);
    info.push_back(person.numberOfFreeze);
    info.push_back(person.armor);
    info.push_back(person.money);
    info.push_back(person.counterhowfast);
    int i;
    if (person.regeneration)
        i = 1;
    else
        i = 0;
    info.push_back(i);

    auto fileName = placeToWrite();

    auto file = std::fstream(
            fileName + ".bin", std::ios::out | std::ios::binary
    );
    file.write(
            reinterpret_cast<char const *>(info.data()),
            sizeof(int) * info.size()
    );
}

auto Load(sf::RenderWindow const &window, Person &person, Level &level) -> void {
    auto info = std::vector<int>(8);

    auto fileName = placeToWrite();

    auto file = std::fstream(
            fileName + ".bin", std::ios::in | std::ios::binary
    );
    file.read(
            reinterpret_cast<char *>(info.data()),
            sizeof(int) * info.size()
    );
    bool regen;
    if (info[6] == 0)
        regen = false;
    else
        regen = true;

    person = Person(info[0], info[1], info[2], info[3], info[4], info[5], regen, info[7]);
    auto levels = Level(window, person);
    if (!person.texture.loadFromFile("../Frog Heaven - assets/Frog.png")) {
        fmt::println("error while loading image ");
        return;
    }
    person.imagine = sf::Sprite(person.texture);

    level = Level(window, person);
    for (int i = 0; i < info[7]; i++) {
        person.velocity.x *= 1.5;
        person.velocity.y *= 1.5;
    }
}
