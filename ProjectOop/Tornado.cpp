#include "Tornado.h"
#include "AssetLoader.h"

Tornado::Tornado(float startX, float startY)
    : FlyngFoogafoog(startX, startY) {
    knifeTimer = 0.0f;
    knifeDuration = 3.0f;
    flyspeedrandomly = 100.0f;
    hp = 4;
}

void Tornado::update(float deltaTime) {
    if (isencased) return;

    // Inherit the flying/ground behavior
    FlyngFoogafoog::update(deltaTime);

    // Tornado specific: Knife throwing
    knifeTimer += deltaTime;
    if (knifeTimer >= knifeDuration) {
        knifeThrow();
        knifeTimer = 0.0f;
    }

    // Unpredictable flight speed changes
    if (getHP() < 2) flyspeedrandomly = 200.0f;

    // Tornado lands on the ground too when not flying
    if (!isFlying) {
        applyGravity(deltaTime);
    }
}
void Tornado::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    enemySprite.setTexture(Assets::tornado_t);
    int frameSize = Assets::tornado_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    enemySprite.setScale(48.0f / frameSize, 48.0f / frameSize);
    window.draw(enemySprite);
}
void Tornado::hit() {
    hp--;
    if (hp <= 0) isencased = true;
}
void Tornado::kill() { hp = 0; isencased = false; }
void Tornado::knifeThrow() {
    // Note: To actually spawn a knife, we'd need to pass the projectile list
    // For now, we will simulate the behavior by resetting the timer.
    // In a full implementation, main.cpp would handle the spawning.
}