#include "Tornado.h"
#include "AssetLoader.h"

Tornado::Tornado(float startX, float startY)
    : FlyngFoogafoog(startX, startY) {
    knifeTimer = 0.0f;
    knifeDuration = 3.0f;
    flyspeedrandomly = 100.0f;
    hp = 4;
    gemdrop = 30;
    enemyType = 3;
}
void Tornado::update(float deltaTime) {
    if (Rolling) {
        FlyngFoogafoog::update(deltaTime);
        return;
    }
    //behavior inherited
    FlyngFoogafoog::update(deltaTime);
    if (get_encased()) {
        return;
    }
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
}
void Tornado::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    static sf::Clock animClock;
    int frame = static_cast<int>(animClock.getElapsedTime().asSeconds() / 0.1f) % 4;
    const Texture* tex = &Assets::tornado_idle_t; 
    if (frame < 3) {
        tex = &Assets::tornado_run_t[frame]; 
    }
    if (tex->getSize().x == 0 || tex->getSize().y == 0) {
        return;
    }
    enemySprite.setTexture(*tex);
    int frameSize = tex->getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    enemySprite.setScale(60.0f / frameSize, 60.0f / frameSize);
    window.draw(enemySprite);
    drawSnowOverlay(window, 60.0f, 60.0f);
}
void Tornado::hit() {
    add_snow(25);
}
void Tornado::kill() { 
    hp = 0; isencased = false;
}
void Tornado::knifeThrow() {
    hasProjectileRequest = true;
    projectileType = "Knife";
    pX = x + 30.0f;
    pY = y + 30.0f;
}

float Tornado::get_knife_timer() const {
    return knifeTimer;
}

float Tornado::get_knife_duration() const {
    return knifeDuration;
}

float Tornado::get_fly_speed_randomly() const {
    return flyspeedrandomly;
}

void Tornado::set_knife_timer(float new_knife_timer) {
    knifeTimer = new_knife_timer;
}

void Tornado::set_knife_duration(float new_knife_duration) {
    knifeDuration = new_knife_duration;
}

void Tornado::set_fly_speed_randomly(float new_fly_speed_randomly) {
    flyspeedrandomly = new_fly_speed_randomly;
}
