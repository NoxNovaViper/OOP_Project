#include "Snowball.h"
Snowball::Snowball(float startX, float startY, float dirX) {
    x = startX;
    y = startY;
    speedX = dirX * 200.0f;
    speedY = 0.0f;
    isactive = true;
    isRolling = false;
    chainCount = 0;
    distanceCovered = 0.0f;
    range = 400.0f;
}

void Snowball::update(float deltaTime) {}
void Snowball::draw() {}
void Snowball::startRolling() {
    isRolling = true;
}