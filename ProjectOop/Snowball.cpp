#include "Snowball.h"
Snowball::Snowball(float startX, float startY, float dirX) {
    x = startX;
    y = startY;
    speedX = dirX * 200.0f;
    speedY = -80.0f;
    vy = speedY;
    isactive = true;
    isRolling = false;
    chainCount = 0;
    distanceCovered = 0.0f;
    range = 400.0f;
    lifetime = 0.0f;
}

void Snowball::update(float Time) {
    // Gravity pulls
    vy += 300.0f * Time;
    //speed decrease
    float drag;
    if (vy > 0.0f) {
        drag = 180.0f;
    }
    else {
        drag = 60.0f;
    }
    if (speedX > 0.0f) {
        speedX -= drag * Time;
        if (speedX < 0.0f) speedX = 0.0f;
    }
    else if (speedX < 0.0f) {
        speedX += drag * Time;
        if (speedX > 0.0f) {
            speedX = 0.0f;
        }
    }
    x += speedX * Time;
    y += vy * Time;
    distanceCovered += abs(speedX * Time);
    //screen wrap
    if (x < 0) {
        x = 800.0f;
    }
    if (x > 800) {
        x = 0.0f;
    }
    //removed if at ground
    if (y > 600.0f) {
        isactive = false;
    }
}
void Snowball::draw(RenderWindow& w) {
    ball.setRadius(16);
    ball.setPosition(x, y);
    ball.setFillColor(Color::Cyan);
    w.draw(ball);
}

void Snowball::startRolling() {
    isRolling = true;
}