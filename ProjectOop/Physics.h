#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Snowball.h"
#include "LevelManager.h"
#include "Projectile.h"
const float gravity = 980.0f;
const float player_h = 50.0f;//for collision measuring
const float Ground = 600.0f;//since 0 is highest and 600 lowest
using namespace std;
using namespace sf;
class snow : public Projectile {
public:
	static int count;
	float dy;
	float dx;
	float max_x;
	float dir;
	float distanceTraveled;
	float maxDistance;
	CircleShape ball;
	void update(float time) override;
	snow(Player& p);
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getHitbox() const override;
	~snow();
};
void jump(Player& p);
void fall(Player& p, float len);
void p_move(Player& p, float speed, float t, bool horizontal);
void attack(Player& p, Projectile** active_projectiles, int& projectile_count);
void Position_change(Player& p, bool vertical, float v, float t, bool horizontal);
bool collision_check(FloatRect Player_hitbox, FloatRect platform_hitbox);
void Fix_collision(Player& p, float platform_top);
void debug_view(Level_Manager& manager, FloatRect Player_hitbox, platform* platforms, int num_platforms, RenderWindow& window);
void draw_debug_box(RenderWindow& window, FloatRect hitbox, Color color);
void Gravity(Player& p, float g, float t);
