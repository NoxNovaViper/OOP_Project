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
    if (Rolling) {
        Botom::update(deltaTime);
        return;
    }
    if (update_snow_state(deltaTime)) {
        return;
    }
    flyTimer += deltaTime;
    if (!isFlying) {
        //Walk when grounded
        Botom::update(deltaTime);
        if (flyTimer >= groundDuration) {
            isFlying = true;
            flyTimer = 0.0f;
            //random fly dir
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
        if (x < 10 || x > 780) {
            speed_x = -speed_x;
        }
        if (y < 10 || y > 580) {
            speed_y = -speed_y;
        }

        if (flyTimer >= flyDuration) {
            isFlying = false;
            flyTimer = 0.0f;
            y = 300; //rest at bottom
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
    drawSnowOverlay(window, 48.0f, 48.0f);
}
void FlyngFoogafoog::hit() {
    add_snow(25);
}
