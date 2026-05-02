#include "Mogera.h"
#include "AssetLoader.h"

Mogera::Mogera(float startX, float startY) {
    x = startX;
    y = startY;
    hp = 15; // Mid-game boss HP
    speed = 50.0f;
    movingRight = true;
    isencased = false;
    gemdrop = 50;
    spawnTimer = 0.0f;
}

void Mogera::update(float deltaTime) {
    if (isencased) return;
    
    // Simple side-to-side movement for the boss
    if (movingRight) {
        x += speed * deltaTime;
        if (x > 700) movingRight = false;
    } else {
        x -= speed * deltaTime;
        if (x < 0) movingRight = true;
    }

    // Apply gravity — boss floor is lower to fit the 100px sprite
    bool was_grounded = on_ground;
    applyGravity(deltaTime, 450.0f);
    // When Mogera lands, give it a bounce-jump
    if (!was_grounded && on_ground) {
        vy = -280.0f;
    }

    // Spawn logic
    spawnTimer += deltaTime;
    if (spawnTimer >= 3.0f) { // Spawn a child every 3 seconds
        spawnTimer = 0.0f;
        hasSpawnRequest = true;
        spawnType = "MogeraChild";
        spawnX = x + 40.0f; // Center horizontally
        spawnY = y + 50.0f;
    }
}
void Mogera::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    enemySprite.setTexture(Assets::mogera_t);
    int frameSize = Assets::mogera_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    enemySprite.setScale(100.0f / frameSize, 100.0f / frameSize);
    window.draw(enemySprite);
}
void Mogera::hit() {
    hp--;
    if (hp <= 0) isencased = true;
}