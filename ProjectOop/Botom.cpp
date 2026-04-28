#include "Botom.h"
Botom::Botom(float startX, float startY) {
    x = startX;
    y = startY;
    hp = 2;
    speed = 40.0f;
    movingRight = true;
    isencased = false;
    gemdrop = 10;
}

void Botom::update(float deltaTime) {}
void Botom::draw() {}
void Botom::hit() {
    hp--;
    if (hp <= 0) isencased = true;
}
