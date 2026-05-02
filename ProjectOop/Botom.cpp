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
        // Screen wrap for rolling snowball
        if (x < 0) x = 800;
        if (x > 800) x = 0;
        return; // Don't do normal logic if rolling
    }

    speed = speed * (1 - (snow / 100));
    if (snow >= 100) {
        speed = 0;
    }
    if ((snow >= 100) && (!Rolling)) {
        Freeze_time += deltaTime * 5; // Speed up freeze recovery slightly
        int freeze_step = static_cast<int>(Freeze_time);
        if (freeze_step >= 20) { snow = 0; Freeze_time = 0; }
        else if (freeze_step >= 16) snow = 20;
        else if (freeze_step >= 12) snow = 40;
        else if (freeze_step >= 8) snow = 60;
        else if (freeze_step >= 4) snow = 80;
    } else if (!isencased) {
        // Restore Patrolling Movement
        if (movingRight) {
            x += speed * deltaTime;
            if (x > 750) movingRight = false;
        } else {
            x -= speed * deltaTime;
            if (x < 10) movingRight = true;
        }
    }

    // Apply gravity so Botom stays on platforms and floors
    applyGravity(deltaTime);
}
void Botom::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    enemySprite.setTexture(Assets::botom_t);
    // Assuming horizontal sprite sheet where frame width == texture height
    int frameSize = Assets::botom_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    // Scale it to fit the 30x30 hitbox approximately
    enemySprite.setScale(48.0f / frameSize, 48.0f / frameSize);
    window.draw(enemySprite);
}
void Botom::hit() {
    hp--;
    if (hp <= 0) {  
        isencased = true;
    }
}
