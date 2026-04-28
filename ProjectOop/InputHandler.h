#pragma once
#include "LevelManager.h"
#include "Physics.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
void Inputhandle(sf::Event& ev, Level_Manager& manager, sf::RenderWindow& window, Player& p1, Player& p2);
