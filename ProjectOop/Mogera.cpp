#include "Mogera.h"
#include "AssetLoader.h"

Mogera::Mogera(float startX, float startY) {
    x = startX;
    y = startY;
    hp = 15; //Mid-game boss HP
    speed = 50.0f;
    movingRight = true;
    isencased = false;
    gemdrop = 50;
    spawnTimer = 0.0f;
}

void Mogera::update(float deltaTime) {
    if (Rolling) {
        x += Roll_speed * deltaTime;
        if (x < 0) x = 800;
        if (x > 800) x = 0;
        return;
    }
    if (update_snow_state(deltaTime)) return;
    //gravity
    bool was_grounded = on_ground;
    applyGravity(deltaTime, 400.0f);
    // When Mogera lands, give it a bouncejump
    if (!was_grounded && on_ground) {
        vy = -280.0f;
    }
    //Spawn logic
    spawnTimer += deltaTime;
    if (spawnTimer >= 3.0f) { //Spawns a child every 3 seconds
        spawnTimer = 0.0f;
        hasSpawnRequest = true;
        spawnType = "MogeraChild";
        spawnX = x + 40.0f; // Center horizontally
        spawnY = y + 80.0f;
        if (spawnY > 480.0f) {
            spawnY = 480.0f;
        }
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
    drawSnowOverlay(window, 100.0f, 100.0f);
}
void Mogera::hit() {
    add_snow(10);
}
