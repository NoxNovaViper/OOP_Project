#pragma once
#include"Botom.h"
#include <SFML/Graphics.hpp>
class FlyngFoogafoog : public Botom {
protected:
	float flyDuration;
	float groundDuration;
	float flyTimer;
	float groundTimer;
	bool isFlying;
	float speed_x, speed_y;

public:
	FlyngFoogafoog(float startX, float startY);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void hit() override;

	float get_fly_duration() const;
	float get_ground_duration() const;
	float get_fly_timer() const;
	float get_ground_timer() const;
	bool get_is_flying() const;
	float get_speed_x() const;
	float get_speed_y() const;

	void set_fly_duration(float new_fly_duration);
	void set_ground_duration(float new_ground_duration);
	void set_fly_timer(float new_fly_timer);
	void set_ground_timer(float new_ground_timer);
	void set_is_flying(bool new_is_flying);
	void set_speed_x(float new_speed_x);
	void set_speed_y(float new_speed_y);
};
