#include "Gamakichi.h"
#include "AssetLoader.h"

Gamakichi::Gamakichi(float startX, float startY)
    : Boss(startX, startY) {
    hp = 30;
    maxhp = 30;
    gemReward = 500;
    attackTimer = 0.0f;
    attackDuration = 2.0f;
    projectileCount = 3;
    armActive = true;
    right = true;
}

void Gamakichi::update(float deltaTime) {
    attackTimer += deltaTime;
    //gravity
    bool was_grounded = on_ground;
    applyGravity(deltaTime, 400.0f);
    //jump on landing
    if (!was_grounded && on_ground) {
        vy = -200.0f;
    }
    //Phase logic updates based on HP in hit()
    if (phase == 1) {
        if (right) { 
            x += 100 * deltaTime;
        } 
        else { 
            x -= 100 * deltaTime; 
        }
        if (x > 700 || x < 0) {
            right = !right;
        }
        
        if (attackTimer >= attackDuration) {
            attackTimer = 0;
            fireArtillery();
        }
    } else if (phase == 2) {
        if (right) { 
            x += 150 * deltaTime;
        } else { 
            x -= 150 * deltaTime;
        }
        if (x > 700 || x < 0) {
            right = !right;
        }
        
        if (attackTimer >= attackDuration) {
            attackTimer = 0;
            fireArtillery();
        }
    } else if (phase == 3) {
        if (right) { 
            x += 250 * deltaTime;
        } else { 
            x -= 250 * deltaTime;
        }
        if (x > 700 || x < 0) {
            right = !right;
        }
        
        if (attackTimer >= attackDuration) {
            attackTimer = 0;
            fireArtillery();
        }
    }
}
void Gamakichi::draw(sf::RenderWindow& window) {
    sf::Sprite enemySprite;
    enemySprite.setTexture(Assets::gamakichi_t);
    int frameSize = Assets::gamakichi_t.getSize().y;
    enemySprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    enemySprite.setPosition(x, y);
    enemySprite.setScale(100.0f / frameSize, 100.0f / frameSize);
    
    // Flash red in frenzy mode
    if (phase == 3) {
        enemySprite.setColor(sf::Color(255, 100, 100));
    }
    
    window.draw(enemySprite);
}
void Gamakichi::hit() {
     hp--;
     //Phase thresholds
     if (hp <= 20 && phase == 1) {
          phase = 2;
          attackDuration = 1.0f; //Attacks 2x as fast
     }
     else if (hp <= 10 && phase == 2) {
         phase = 3;
         attackDuration = 0.5f; //Attacks 4x as fast
     }
     if (hp <= 0)
        isdefeated = true;
}
void Gamakichi::phaseChange() {}
void Gamakichi::fireArtillery() {
    //projectile spawn
    hasProjectileRequest = true;
    projectileType = "Artillery";
    pX = x + 50.0f; //center
    pY = y;
    //Fires randomly either left or right arc
    pVy = -400.0f; //shoots up
    pVx = (rand() % 2 == 0) ? 200.0f : -200.0f;
}
