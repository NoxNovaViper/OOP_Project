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
    gemdrop = 20;
    enemyType = 2;
}

void FlyngFoogafoog::update(float deltaTime) {
    if (Rolling) {
        Botom::update(deltaTime);
        return;
    }
    flyTimer += deltaTime;
    if (!isFlying) {
        //Walk when grounded
        Botom::update(deltaTime);
        if (flyTimer >= groundDuration) {
            isFlying = true;
            flyTimer = 0.0f;
            if (rand() % 2 == 0) {
                speed_x = 120.0f;
            }
            else {
                speed_x = -120.0f;
            }
            if (rand() % 2 == 0) {
                speed_y = 80.0f;
            }
            else {
                speed_y = -80.0f;
            }
        }
    }
    else {
        //free flight, move over screen
        x += speed_x * snow_speed_multiplier() * deltaTime;
        y += speed_y * snow_speed_multiplier() * deltaTime;
        //Bounce off
        if ((x < 50) || (x > 750)) {
            speed_x = -speed_x;
        }
        if ((y < 10) || (y > 580)) {
            speed_y = -speed_y;
        }
        if (flyTimer >= flyDuration) {
            isFlying = false;
            flyTimer = 0.0f;
            y = 300;//rest at bottom
        }
    }
}
void FlyngFoogafoog::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    static sf::Clock animClock;
    int frame = static_cast<int>(animClock.getElapsedTime().asSeconds() / 0.12f) % 4;
    const Texture* tex = &Assets::flyng_t;
    if (Assets::flyng_anim[frame].getSize().x > 0 && Assets::flyng_anim[frame].getSize().y > 0) {
        tex = &Assets::flyng_anim[frame];
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
void FlyngFoogafoog::hit() {
    add_snow(25);
}

float FlyngFoogafoog::get_fly_duration() const {
    return flyDuration;
}

float FlyngFoogafoog::get_ground_duration() const {
    return groundDuration;
}

float FlyngFoogafoog::get_fly_timer() const {
    return flyTimer;
}

float FlyngFoogafoog::get_ground_timer() const {
    return groundTimer;
}

bool FlyngFoogafoog::get_is_flying() const {
    return isFlying;
}

float FlyngFoogafoog::get_speed_x() const {
    return speed_x;
}

float FlyngFoogafoog::get_speed_y() const {
    return speed_y;
}

void FlyngFoogafoog::set_fly_duration(float new_fly_duration) {
    flyDuration = new_fly_duration;
}

void FlyngFoogafoog::set_ground_duration(float new_ground_duration) {
    groundDuration = new_ground_duration;
}

void FlyngFoogafoog::set_fly_timer(float new_fly_timer) {
    flyTimer = new_fly_timer;
}

void FlyngFoogafoog::set_ground_timer(float new_ground_timer) {
    groundTimer = new_ground_timer;
}

void FlyngFoogafoog::set_is_flying(bool new_is_flying) {
    isFlying = new_is_flying;
}

void FlyngFoogafoog::set_speed_x(float new_speed_x) {
    speed_x = new_speed_x;
}

void FlyngFoogafoog::set_speed_y(float new_speed_y) {
    speed_y = new_speed_y;
}
