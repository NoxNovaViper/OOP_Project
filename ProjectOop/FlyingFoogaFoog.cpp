#include"FlyngFoogaFoog.h"
#include "AssetLoader.h"
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

void FlyngFoogafoog::update(float deltaTime) {
    if (isencased) return;

    flyTimer += deltaTime;
    if (!isFlying) {
        // Ground behavior: Walk like a Botom
        Botom::update(deltaTime);
        if (flyTimer >= groundDuration) {
            isFlying = true;
            flyTimer = 0.0f;
            // Pick a random flying direction
            speed_x = (rand() % 2 == 0) ? 120.0f : -120.0f;
            speed_y = (rand() % 2 == 0) ? 80.0f : -80.0f;
        }
    }
    else {
        // Flight behavior: Move freely
        x += speed_x * deltaTime;
        y += speed_y * deltaTime;

        // Bounce off screen edges
        if (x < 10 || x > 780) speed_x = -speed_x;
        if (y < 10 || y > 580) speed_y = -speed_y;

        if (flyTimer >= flyDuration) {
            isFlying = false;
            flyTimer = 0.0f;
            y = 300; // Reset to a middle ground level
        }
    }
}
void FlyngFoogafoog::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    enemySprite.setTexture(Assets::flyng_t);
    int frameSize = Assets::flyng_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    enemySprite.setScale(48.0f / frameSize, 48.0f / frameSize);
    window.draw(enemySprite);
}
void FlyngFoogafoog::hit() {
    hp--;
    if (hp <= 0) isencased = true;
}