#pragma once
#include "LevelManager.h"
#include "Physics.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;
void Inputhandle(Event& ev, Level_Manager& manager, RenderWindow& window, Player& p1, Player& p2, Projectile** projectiles, int& count);
