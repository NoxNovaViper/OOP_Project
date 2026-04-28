#include "Knife.h"
#include <cmath>

Knife::Knife(float startX, float startY, float targetX, float targetY) {
    x = startX;
    y = startY;
    damage = 1.0f;
    isactive = true;
    float dx = targetX - startX;
    float dy = targetY - startY;
    float length = sqrt(dx * dx + dy * dy);
    speedX = (dx / length) * 150.0f;
    speedY = (dy / length) * 150.0f;
}

void Knife::update(float deltaTime) {}
void Knife::draw() {}