#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "fstream"

auto delatelast(sf::String str) -> sf::String;

auto delatelast(sf::String str) -> sf::String;

auto placeToWrite() -> std::string;

auto Saving(Person const &person, Level const &level) -> void;

auto Load(sf::RenderWindow const &window, Person &person, Level &level) -> void;