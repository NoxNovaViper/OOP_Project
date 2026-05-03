#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "LevelManager.h"
#include "Physics.h"
#include <ctime>
#include <cstdlib>
using namespace sf;
using namespace std;
class Enemy {
protected:
	float jump_power;
	float x, y;
	int hp;
	int gemdrop;
	bool isencased;
	float speed;
	bool movingRight; // Added for direction control

	//Gravity
	float vy;
	bool on_ground;

	//new
	int snow;
	float Freeze_time;
	float Roll_speed;
	bool Rolling;
	float rollScale;
	int enemyType;
	int rollingOwner;
	Sprite sprite;
	Texture texture;
	FloatRect hitbox;

public:
	bool hasSpawnRequest;
	string spawnType;
	float spawnX, spawnY;

	bool hasProjectileRequest;
	string projectileType;
	float pX, pY, pVx, pVy;

	Enemy() : x(0), y(0), hp(0), gemdrop(0), isencased(false), speed(0),vy(0.0f), on_ground(false),
	snow(0), Freeze_time(0.0f), Rolling(false), Roll_speed(0.0f), rollScale(1.0f), enemyType(0), rollingOwner(0),
	hasSpawnRequest(false), spawnType(""), spawnX(0), spawnY(0),
	hasProjectileRequest(false), projectileType(""), pX(0), pY(0), pVx(0), pVy(0), jump_power(100.0f) {}
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual void hit() = 0;
	virtual ~Enemy() {}
	virtual void kill() { hp = 0; isencased = false; }
	void add_snow(int amount) {
		if ((Rolling) || (hp <= 0)) {
			return;
		}
		snow += amount;
		Freeze_time = 0.0f;
		if (snow >= 100) {
			snow = 100;
			isencased = true;
		}
	}
	bool update_snow_state(float deltaTime) {
		if (Rolling) return true;
		if (snow > 0 && !isencased) {
			Freeze_time += deltaTime;
			if (Freeze_time >= 2.0f) {
				snow -= 20;
				if (snow < 0) snow = 0;
				Freeze_time = 0.0f;
			}
		}
		if (isencased) {
			Freeze_time += deltaTime;
			if (Freeze_time >= 8.0f) {
				snow = 0;
				Freeze_time = 0.0f;
				isencased = false;
				return false;
			}
			return true;
		}
		return false;
	}
	void jump() {
		if (on_ground) {
			vy = -jump_power;
		}
	}
	//Gravity function
	void applyGravity(float Time, float f = 500.0f) {
		vy += 600 * Time;
		y += vy * Time;
		if (y >= f) {
			y = f;
			vy = 0.0f;
			on_ground = true;
		}
		else {
			on_ground = false;
		}
	}
	//Platform collision for enemies
	void check_platform_collision(level* lvl) {
		if (lvl == nullptr) return;
		on_ground = false;
		float enemy_bottom = y + getHitbox().height;
		for (int i = 0; i < lvl->num_platforms; i++) {
			platform pt = lvl->platforms[i];
			if (vy >= 0 && getHitbox().intersects(pt.collison)) {
				if (enemy_bottom - pt.y < 30.0f) {
					y = pt.y - getHitbox().height;
					vy = 0;
					on_ground = true;
					break;
				}
			}
		}
		if (y >= 500.0f) {
			y = 500.0f;
			vy = 0;
			on_ground = true;
		}
	}
	float snow_speed_multiplier() const {
		float multiplier = 1.0f - (static_cast<float>(snow) / 100.0f);
		if (multiplier < 0.2f) {
			return 0.2f;
		}
		else{
			return  multiplier;
		}
	}
	void grow_rolling() {
		rollScale += 0.25f;
		if (rollScale > 2.0f) {
			rollScale = 2.0f;
		}
	}
	int get_snow() const {
		return snow;
	}
	float get_roll_scale() const {
		return rollScale;
	}
	int getHP() const {
		return hp;
	}
	virtual int get_max_hp() const {
		return 1;
	}
	int get_gemdrop() const {
		return gemdrop;
	}
	bool get_encased() const {
		return isencased;
	}
	bool get_rolling() const {
		return Rolling;
	}
	float get_roll_speed() const {
		return Roll_speed;
	}
	int get_enemy_type() const {
		return enemyType;
	}
	int get_rolling_owner() const {
		return rollingOwner;
	}
	void start_rolling(float v, int owner = 0) {
		Rolling = true;
		Roll_speed = v;
		rollingOwner = owner;
		isencased = true;
		snow = 100;
	}
	float getx() {
		return x;
	}
	float gety() {
		return y;
	}
	float get_speed() {
		return speed;
	}
	float get_vy() {
		return vy;
	}
	bool get_on_ground() {
		return on_ground;
	}
	Sprite& get_sprite() {
		return sprite;
	}
	Texture& get_texture() {
		return texture;
	}
	void set_x(float _x) {
		x = _x;
	}
	void set_y(float _y) {
		y = _y;
	}
	void set_hp(int h) {
		hp = h;
	}
	void set_gemdrop(int g) {
		gemdrop = g;
	}
	void set_encased(bool e) {
		isencased = e;
	}
	void set_speed(float s) {
		speed = s;
	}
	void set_vy(float v) {
		vy = v;
	}
	void set_on_ground(bool g) {
		on_ground = g;
	}
	void set_snow(int s) {
		snow = s;
		if (snow < 0) {
			snow = 0;
		}
		if (snow > 100) {
			snow = 100;
		}
		isencased = (snow >= 100);
	}
	void set_freeze_time(float t) {
		Freeze_time = t;
	}
	void set_rolling(bool r) {
		Rolling = r;
	}
	void set_roll_speed(float s) {
		Roll_speed = s;
	}
	void set_roll_scale(float r) {
		rollScale = r;
	}
	void set_enemy_type(int t) {
		enemyType = t;
	}
	void set_rolling_owner(int owner) {
		rollingOwner = owner;
	}
	void set_sprite(const Sprite& s) {
		sprite = s;
	}
	void set_texture(const Texture& t) {
		texture = t;
	}
	void set_hitbox(const FloatRect& h) {
		hitbox = h;
	}
	virtual FloatRect getHitbox() const {
		float s;
		if (Rolling) {
			s = 60.0f * rollScale;
		}
		else {
			s = 60;
		}
		return FloatRect(x, y, s, s);
	}
	void drawSnowOverlay(sf::RenderWindow& window, float width, float height) const {
		if (snow <= 0 && !Rolling) return;
		float size = (width > height ? width : height) * (0.35f + 0.65f * (static_cast<float>(snow) / 100.0f));
		if (Rolling) size = width * rollScale;
		sf::CircleShape coat(size / 2.0f);
		coat.setPosition(x + (width - size) / 2.0f, y + (height - size) / 2.0f);
		coat.setFillColor(sf::Color(230, 250, 255, isencased || Rolling ? 190 : 90));
		coat.setOutlineColor(sf::Color::White);
		coat.setOutlineThickness(2.0f);
		window.draw(coat);
	}
};
