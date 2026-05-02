#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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
	float rollScale;

	void applyGravity(float deltaTime, float floorY = -1.0f) {
		if (floorY < 0.0f) {
			floorY = 500.0f - getHitbox().height;
		}
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
	snow(0), Freeze_time(0.0f), Rolling(false), Roll_speed(0.0f), rollScale(1.0f),
	hasSpawnRequest(false), spawnType(""), spawnX(0), spawnY(0),
	hasProjectileRequest(false), projectileType(""), pX(0), pY(0), pVx(0), pVy(0) {}
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void hit() = 0;
	virtual ~Enemy() {}
	virtual void kill() { hp = 0; isencased = false; }
	void add_snow(int amount) {
		if (Rolling || hp <= 0) return;
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
	float snow_speed_multiplier() const {
		float multiplier = 1.0f - (static_cast<float>(snow) / 100.0f);
		return multiplier < 0.2f ? 0.2f : multiplier;
	}
	void grow_rolling() {
		rollScale += 0.25f;
		if (rollScale > 2.0f) rollScale = 2.0f;
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
	bool get_encased() const {
		return isencased;
	}
	bool get_rolling() const {
		return Rolling;
	}
	void start_rolling(float speed_val) {
		Rolling = true;
		Roll_speed = speed_val;
		isencased = true;
		snow = 100;
	}
	float getx() const {
		return x;
	}
	float gety() const {
		return y;
	}
	virtual sf::FloatRect getHitbox() const {
		float size = Rolling ? 48.0f * rollScale : 48.0f;
		return sf::FloatRect(x, y, size, size);
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
