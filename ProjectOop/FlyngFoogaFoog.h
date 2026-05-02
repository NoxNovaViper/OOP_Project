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

};