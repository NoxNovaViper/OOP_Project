#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelManager.h"
const float player_h = 50.0f;//for collision measuring
const float Ground = 600.0f;//since 0 is highest and 600 lowest
void jump(float& v, float len, bool on_ground);
void fall(float& v, float len, bool on_ground);
void p_move(float len, float sp, float t, bool h);
void attack();
void Gravity(float& v, float g, float t);
void Position_change(float& s, float v, float t, bool h);
float Position_check(float s, float v, float t);
bool collision_check(FloatRect Player_hitbox, float y, float v, float t, FloatRect platform_hitbox);
void Fix_collision(float& s, float& v, Platform_Maker& platform);
void debug_view(Level_Manager& manager, FloatRect Player_hitbox, platform* platforms, int num_platforms, RenderWindow& window);