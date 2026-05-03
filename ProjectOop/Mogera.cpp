#include "Mogera.h"
#include "AssetLoader.h"

Mogera::Mogera(float startX, float startY) : Boss(startX, startY) {
    x = 700.0f; //Spawn on the right
    y = startY;
    hp = 20;//Boss HP
    maxhp = 20;
    speed = 50.0f;
    movingRight = true;
    isencased = false;
    gemdrop = 100; //currency reward
    spawnTimer = 0.0f;
    enemyType = 4;
    jump_power = 400.0f;
}

void Mogera::update(float deltaTime) {
    if (Rolling) {
        x += Roll_speed * deltaTime;
        applyGravity(deltaTime);
        if ((x <= 0) || (x + getHitbox().width >= 800)) {
            kill();
        }
        return;
    }
    //jump logic vertically only
    if (on_ground) {
        jump();
    }
    //gravity and pos change
    applyGravity(deltaTime);
    
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
    hp--;
    if (hp <= 0) {
        isdefeated = true;
    }
}
void Mogera::phaseChange() {}

bool Mogera::get_moving_right() const {
    return movingRight;
}

float Mogera::get_spawn_timer() const {
    return spawnTimer;
}

void Mogera::set_moving_right(bool new_moving_right) {
    movingRight = new_moving_right;
}

void Mogera::set_spawn_timer(float new_spawn_timer) {
    spawnTimer = new_spawn_timer;
}
void Mogera::child_throw() {

}
void Mogera::jump() {
    if (on_ground) {
        vy = -jump_power;
        on_ground = false;
    }
}
void Mogera::fall() {
    if (y < 550) {

    }

}
