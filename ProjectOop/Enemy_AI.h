#pragma once
#include "Physics.h"
#include "Player.h"
#include "LevelManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "EnemyFactory.h"
#include "Enemy.h"
#include "FlyngFoogaFoog.h"
#include "Botom.h"
#include "Mogera.h"
using namespace std;
using namespace sf;
bool search(int player_x, int enemy_x, int player_y, int enemy_y);
void update_fireball(CircleShape& fireball, bool& active, FloatRect player_hitbox);
void Frozen();
void flying_enemy_movement(Enemy* e, float deltaTime);
void ground_enemy_movement(Enemy* e, float deltaTime);
void defrost();
bool check_player_enemy_collision(Player& p, Enemy* e);
bool check_projectile_enemy_collision(FloatRect projectile_hitbox, Enemy* e);
bool direction_check(Player& p, Enemy* e);
void Gravity(Enemy* e, float g, float t);
