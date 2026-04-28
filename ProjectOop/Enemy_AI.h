#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Physics.h"
using namespace std;
using namespace sf;
bool search(int player_x, int enemy_x, int player_y, int enemy_y);
void update_fireball(CircleShape& fireball, bool& active, FloatRect player_hitbox);
void Frozen();
void defrost();
