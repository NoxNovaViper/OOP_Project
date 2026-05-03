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
    enemyType = 1;
}

void Botom::update(float deltaTime) {
    if (Rolling) {
        x += Roll_speed * deltaTime;
        applyGravity(deltaTime);
        if ((x <= 0) || (x + getHitbox().width >= 800)) {
            kill();
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
            if (x > 750) {
                movingRight = false;
            }
        } else {
            x -= currentSpeed * deltaTime;
            if (x < 10) {
                movingRight = true;
            }
        }
    }

    //gravity
    applyGravity(deltaTime);
}
void Botom::draw(sf::RenderWindow& window) {
    Sprite enemySprite;
    enemySprite.setTexture(Assets::botom_t);
    int frameSize = Assets::botom_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);

    enemySprite.setScale(60.0f / frameSize, 60.0f / frameSize);
    window.draw(enemySprite);
    drawSnowOverlay(window, 60.0f, 60.0f);
}
void Botom::hit() {
    add_snow(50);
}

bool Botom::get_moving_right() const {
    return movingRight;
}

void Botom::set_moving_right(bool r) {
    movingRight = r;
}
