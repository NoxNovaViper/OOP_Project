#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "LevelManager.h"
const float player_h = 50.0f;//for collision measuring
const float Ground = 600.0f;//since 0 is highest and 600 lowest
using namespace std;
using namespace sf;
void jump(Player& p);
void fall(Player& p, float len);
void p_move(Player& p, float speed, float t, bool horizontal);
void attack(Player& p);
void Position_change(Player& p, bool vertical, float v, float t, bool horizontal);
bool collision_check(FloatRect Player_hitbox, FloatRect platform_hitbox);
void Fix_collision(Player& p);
void debug_view(Level_Manager& manager, FloatRect Player_hitbox, platform* platforms, int num_platforms, RenderWindow& window);
void Gravity(Player& p, float g, float t);