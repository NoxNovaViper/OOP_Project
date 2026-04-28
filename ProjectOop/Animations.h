#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include <string>
using namespace std;
using namespace sf;
void load_assets(Player& p);
void update_animations(Player& p, float deltaTime, bool left, bool right);
