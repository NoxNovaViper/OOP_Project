#include "Snowball.h"
Snowball::Snowball(float startX, float startY, float dirX) {
    x = startX;
    y = startY;
    speedX = dirX * 200.0f;
    speedY = -80.0f;  // slight upward arc on throw
    vy = speedY;
    isactive = true;
    isRolling = false;
    chainCount = 0;
    distanceCovered = 0.0f;
    range = 400.0f;
    lifetime = 0.0f;
}

void Snowball::update(float Time) {
    lifetime += Time;
    if (lifetime >= 4.0f) {   // 4-second cap
        isactive = false;
        return;
    }

    // Gravity pulls the ball down
    vy += 300.0f * Time;

    // X-axis drag: triple decay when falling (vy > 0 means descending)
    float drag = (vy > 0.0f) ? 180.0f : 60.0f;
    if (speedX > 0.0f) {
        speedX -= drag * Time;
        if (speedX < 0.0f) speedX = 0.0f;
    } else if (speedX < 0.0f) {
        speedX += drag * Time;
        if (speedX > 0.0f) speedX = 0.0f;
    }

    x += speedX * Time;
    y += vy * Time;

    distanceCovered += abs(speedX * Time);

    // Screen wrap
    if (x < 0)   x = 800.0f;
    if (x > 800) x = 0.0f;

    // Kill if it falls off the bottom of the screen
    if (y > 620.0f) isactive = false;
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