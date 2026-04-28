#include"FlyngFoogaFoog.h"
FlyngFoogafoog::FlyngFoogafoog(float startX, float startY)
    : Botom(startX, startY) {
    isFlying = false;
    flyTimer = 0.0f;
    flyDuration = 4.0f;
    groundTimer = 0.0f;
    groundDuration = 3.0f;
    speed_x = 80.0f;
    speed_y = 60.0f;
    hp = 3;
}

void FlyngFoogafoog::update(float deltaTime) {}
void FlyngFoogafoog::draw() {}
void FlyngFoogafoog::hit() {
    hp--;
    if (hp <= 0) isencased = true;
}