#pragma once
#include"Botom.h"
class FlyngFoogafoog : public Botom {
private:
	float flyDuration;
	float groundDuration;
	float flyTimer;
	float groundTimer;
	bool isFlying;
	float speed_x, speed_y;

public:
	FlyngFoogafoog(float startX, float startY);
	void update(float deltaTime) override;
	void draw() override;
	void hit() override;

};