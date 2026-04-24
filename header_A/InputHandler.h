#pragma once
#include "LevelManager.h"
#include "Physics.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
void Inputhandle(Event& ev, Level_Manager& manager, RenderWindow& window);

struct Player {
    float x, y;
    float vx, vy;
    float speed = 200.0f;
    float jump_power = 600.0f;
    bool on_ground = false;
    sf::FloatRect hitbox;
};//temp player struct