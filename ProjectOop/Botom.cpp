#include "Botom.h"
#include "AssetLoader.h"
Botom::Botom(float startX, float startY) {
    x = startX;
    y = startY;
    hp = 2;
    speed = 40.0f;
    movingRight = true;
    isencased = false;
    gemdrop = 10;
}

void Botom::update(float deltaTime) {
    if (Rolling) {
        x += Roll_speed * deltaTime;
        //When snowball, so rolling
        if (x < 0) {
            x = 800;
        }
        if (x > 800) {
            x = 0;
        }
        return;//no normal logic for rolling
    }

    if (update_snow_state(deltaTime)) {
        return;
    }

    float currentSpeed = speed * snow_speed_multiplier();
    if (!isencased) {
        //movement back
        if (movingRight) {
            x += currentSpeed * deltaTime;
            if (x > 750) movingRight = false;
        } else {
            x -= currentSpeed * deltaTime;
            if (x < 10) movingRight = true;
        }
    }

    //gravity
    applyGravity(deltaTime);
}
void Botom::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    enemySprite.setTexture(Assets::botom_t);
    int frameSize = Assets::botom_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    //scaled
    enemySprite.setScale(48.0f / frameSize, 48.0f / frameSize);
    window.draw(enemySprite);
    drawSnowOverlay(window, 48.0f, 48.0f);
}
void Botom::hit() {
    add_snow(25);
}
