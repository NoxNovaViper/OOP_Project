#include "Gamakichi.h"

Gamakichi::Gamakichi(float startX, float startY)
    : Boss(startX, startY) {
    hp = 30;
    maxhp = 30;
    gemReward = 500;
    attackTimer = 0.0f;
    attackDuration = 2.0f;
    projectileCount = 3;
    armActive = true;
}

void Gamakichi::update(float deltaTime) {}
void Gamakichi::draw() {}
void Gamakichi::hit() {
    hp--;
    if (hp <= 8)
        phase = 2;
    if (hp <= 0)
        isdefeated = true;
}
void Gamakichi::phaseChange() {}
void Gamakichi::fireArtillery() {}