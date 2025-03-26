#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"


auto pauseBetweenLevels(sf::RenderWindow &window, Person &person, Level &level) -> void;

auto endGame(sf::RenderWindow &window, Person &person, Level &level) -> void;

auto ShowInfo(sf::RenderWindow &window, Person const &person) -> void;

auto Shop(sf::RenderWindow &window, Person &person) -> void;

auto Pauza(sf::RenderWindow &window, Person &person, Level &level) -> void;