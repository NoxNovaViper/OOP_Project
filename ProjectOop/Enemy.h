#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
protected:
	float x, y;
	int hp;
	int gemdrop;
	bool isencased;
	float speed;

	// Gravity
	float vy;
	bool on_ground;

	//new
	int snow;
	float Freeze_time;
	float Roll_speed;
	bool Rolling;

	void applyGravity(float deltaTime, float floorY = 452.0f) {
		vy += 600.0f * deltaTime;
		y += vy * deltaTime;
		if (y >= floorY) {
			y = floorY;
			vy = 0.0f;
			on_ground = true;
		} else {
			on_ground = false;
		}
	}
public:
	bool hasSpawnRequest;
	std::string spawnType;
	float spawnX, spawnY;

	bool hasProjectileRequest;
	std::string projectileType;
	float pX, pY, pVx, pVy;

	Enemy() : x(0), y(0), hp(0), gemdrop(0), isencased(false), speed(0),
	vy(0.0f), on_ground(false),
	snow(0), Freeze_time(0.0f), Rolling(false), Roll_speed(0.0f),
	hasSpawnRequest(false), spawnType(""), spawnX(0), spawnY(0),
	hasProjectileRequest(false), projectileType(""), pX(0), pY(0), pVx(0), pVy(0) {}
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void hit() = 0;
	virtual ~Enemy() {}
	virtual void kill() { hp = 0; isencased = false; }
	int getHP() const {
		return hp;
	}
	bool get_encased() const {
		return isencased;
	}
	bool get_rolling() const {
		return Rolling;
	}
	void start_rolling(float speed_val) {
		Rolling = true;
		Roll_speed = speed_val;
	}
	float getx() const {
		return x;
	}
	float gety() const {
		return y;
	}
	virtual sf::FloatRect getHitbox() const {
		return sf::FloatRect(x, y, 48.0f, 48.0f);
	}

};