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
    if (Rolling) {
        FlyngFoogafoog::update(deltaTime);
        return;
    }
    if (update_snow_state(deltaTime)) return;
    //behavior inherited
    FlyngFoogafoog::update(deltaTime);
    //knife throw
    knifeTimer += deltaTime;
    if (knifeTimer >= knifeDuration) {
        knifeThrow();
        knifeTimer = 0.0f;
    }
    //random tp
    if (getHP() < 2) {
        flyspeedrandomly = 200.0f;
    }
    //on land
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
    drawSnowOverlay(window, 48.0f, 48.0f);
}
void Tornado::hit() {
    add_snow(25);
}
void Tornado::kill() { 
    hp = 0; isencased = false;
}
void Tornado::knifeThrow() {
//didnt do rn
}
