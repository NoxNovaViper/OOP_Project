#include "Mogera.h"
#include "AssetLoader.h"

Mogera::Mogera(float startX, float startY) : Boss(startX, startY) {
    x = 700.0f; //Spawn on the right
    y = startY;
    hp = 20;//Boss HP
    max_hp = 20;
    speed = 50.0f;
    movingRight = true;
    isencased = false;
    gemdrop = 100; //currency reward
    spawnTimer = 0.0f;
    enemy_type = 4;
    jump_power = 400.0f;
}

void Mogera::update(float Time) {
    if (Rolling) {
        x += Roll_speed * Time;
        applyGravity(Time);
        if ((x <= 0) || (x + getHitbox().width >= 800)) {
            kill();
        }
        return;
    }
    // No horizontal movement as per user request
    
    // Jump logic: only if platform above
    if (on_ground && curr_level_pt != nullptr) {
        bool platform_above = false;
        for (int i = 0; i < curr_level_pt->num_platforms; i++) {
            platform& pt = curr_level_pt->platforms[i];
            // If platform is above and overlapping horizontally
            if (pt.y < y && pt.x < x + 100.0f && pt.x + pt.w > x) {
                // Also check if it's not too far up? Let's say within 200px
                if (y - pt.y < 300.0f && y - pt.y > 50.0f) {
                    platform_above = true;
                    break;
                }
            }
        }
        if (platform_above) {
            jump();
        }
    }
    //gravity and pos change
    applyGravity(Time);
    
    //Spawn logic
    spawnTimer += Time;
    if (spawnTimer >= 3.0f) { //Spawns a child every 3 seconds
        spawnTimer = 0.0f;
        spawn = true;
        spawn_type = "MogeraChild";
        spawn_x = x + 40.0f; // Center horizontally
        spawn_y = y + 20.0f; // Start higher for throw
        spawn_vx = movingRight ? 200.0f : -200.0f; // Throw in moving direction
        spawn_vy = -300.0f; // Throw in arc
    }
    if (spawn_y > 480.0f) {
        spawn_y = 480.0f;
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
        is_defeated = true;
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
