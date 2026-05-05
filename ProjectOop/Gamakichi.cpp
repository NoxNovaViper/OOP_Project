#include "Gamakichi.h"
#include "AssetLoader.h"

Gamakichi::Gamakichi(float startX, float startY)
    : Boss(startX, startY) {
    hp = 30;
    max_hp = 30;
    gem_reward = 500;
    attackTimer = 0.0f;
    attackDuration = 2.5f;
    projectileCount = 3;
    x = 350.0f;
    y = startY;
    armActive = true;
    right = true;
    enemy_type = 5;
    phase = 1;
    jumpTimer = 0.0f;
    jumpDuration = 3.0f;
    fireQueue = 0;
    fireDelayTimer = 0.0f;
}

void Gamakichi::update(float Time) {
    if (Rolling) {
        x += Roll_speed * Time;
        applyGravity(Time);
        if ((x <= 0) || (x + getHitbox().width >= 800)) {
            kill();
        }
        return;
    }

    attackTimer += Time;
    jumpTimer += Time;

    // Phase thresholds — set here so phase updates during update()
    if (hp <= 20 && hp > 10 && phase == 1) {
        phase = 2;
        attackDuration = 1.5f;
    }
    else if (hp <= 10 && phase == 2) {
        phase = 3;
        attackDuration = 0.8f;
    }

    // Gravity — use 500 floor (screen bottom)
    applyGravity(Time, 500.0f);

    // Horizontal movement — speed increases per phase
    float move_speed = 80.0f;
    if (phase == 2) move_speed = 130.0f;
    if (phase == 3) move_speed = 200.0f;

    if (right) {
        x += move_speed * Time;
        if (x > 680) right = false;
    }
    else {
        x -= move_speed * Time;
        if (x < 20) right = true;
    }

    // Jump periodically in phase 2+
    if (phase >= 2 && jumpTimer >= jumpDuration) {
        jumpTimer = 0.0f;
        if (on_ground) {
            vy = -450.0f;
            on_ground = false;
        }
    }

    // Process fire queue
    if (fireQueue > 0) {
        fireDelayTimer += Time;
        if (fireDelayTimer >= 0.15f) {
            fireDelayTimer = 0.0f;
            if (fireQueue == 3) fireArtillery(-100.0f);
            else if (fireQueue == 2) fireArtillery(0.0f);
            else if (fireQueue == 1) fireArtillery(100.0f);
            fireQueue--;
        }
    }

    // Fire artillery
    if (attackTimer >= attackDuration && fireQueue == 0) {
        attackTimer = 0.0f;
        // In phase 3 fire a spread of 3 sequentially
        if (phase == 3) {
            fireQueue = 3;
            fireDelayTimer = 0.15f;
        }
        else {
            fireArtillery(0.0f);
        }
    }
}

void Gamakichi::draw(sf::RenderWindow& window) {
    // Body
    sf::Sprite bodySprite;
    const sf::Texture* bodyTex = (phase >= 2) ? &Assets::gamakichi_t : &Assets::gamakichi_t;
    // Use second sprite in phase 3 if available
    bodySprite.setTexture(*bodyTex);
    sf::Vector2u sz = bodyTex->getSize();
    float scale = 100.0f / (float)sz.y;
    bodySprite.setScale(right ? scale : -scale, scale);
    bodySprite.setPosition(right ? x : x + 100.0f, y);
    if (phase == 3) {
        bodySprite.setColor(sf::Color(255, 100, 100)); // red tint in frenzy
    }
    else if (phase == 2) {
        bodySprite.setColor(sf::Color(255, 200, 100)); // orange tint
    }
    else {
        bodySprite.setColor(sf::Color::White);
    }
    window.draw(bodySprite);

    // Left arm
    sf::Sprite leftArm;
    leftArm.setTexture(Assets::gamakichi_arms[0]);
    sf::Vector2u la = Assets::gamakichi_arms[0].getSize();
    leftArm.setScale(50.0f / la.x, 50.0f / la.y);
    leftArm.setPosition(x - 40.0f, y + 20.0f);
    window.draw(leftArm);

    // Right arm
    sf::Sprite rightArm;
    rightArm.setTexture(Assets::gamakichi_arms[1]);
    sf::Vector2u ra = Assets::gamakichi_arms[1].getSize();
    rightArm.setScale(50.0f / ra.x, 50.0f / ra.y);
    rightArm.setPosition(x + 90.0f, y + 20.0f);
    window.draw(rightArm);

    // Snow overlay if encased
    drawSnowOverlay(window, 100.0f, 100.0f);
}

void Gamakichi::hit() {
    hp--;
    if (hp <= 0) {
        is_defeated = true;
        hp = 0;
    }
}

void Gamakichi::phaseChange() {}

void Gamakichi::fireArtillery(float xOffset) {
    projectile = true;
    projectileType = "Artillery";
    px = x + 50.0f;
    py = y + 10.0f;
    pvy = -480.0f;
    pvx = xOffset; // main.cpp will add player-aimed velocity on top for center shot
}

float Gamakichi::get_attack_timer() const { return attackTimer; }
float Gamakichi::get_attack_duration() const { return attackDuration; }
int Gamakichi::get_projectile_count() const { return projectileCount; }
bool Gamakichi::get_arm_active() const { return armActive; }
void Gamakichi::set_attack_timer(float t) { attackTimer = t; }
void Gamakichi::set_attack_duration(float d) { attackDuration = d; }
void Gamakichi::set_projectile_count(int c) { projectileCount = c; }
void Gamakichi::set_arm_active(bool a) { armActive = a; }