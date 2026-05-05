#include "ArtilleryProjectile.h"
#include "AssetLoader.h"

ArtilleryProjectile::ArtilleryProjectile(float startX, float startY, float startVx, float startVy) {
    x = startX;
    y = startY;
    vx = startVx;
    vy = startVy;
    isactive = true;
    is_hit = false;
    exploding = false;
    explodeTimer = 0.0f;
    explodeFrame = 0;
}

void ArtilleryProjectile::update(float Time) {
    if (!isactive) return;

    if (exploding) {
        explodeTimer += Time;
        explodeFrame = (int)(explodeTimer / 0.08f);
        if (explodeFrame >= 4) {
            isactive = false;
        }
        return; // don't move while exploding
    }

    // Arc movement with gravity
    vy += 500.0f * Time;
    x += vx * Time;
    y += vy * Time;

    // Explode on hitting floor
    if (y >= 490.0f) {
        y = 490.0f;
        exploding = true;
        explodeTimer = 0.0f;
        explodeFrame = 0;
        vx = 0; vy = 0;
    }

    // Despawn off screen sides
    if (x < -20.0f || x > 820.0f) {
        isactive = false;
    }
}

void ArtilleryProjectile::draw(RenderWindow& window) {
    if (!isactive) return;

    if (exploding) {
        // Draw explosion frames
        int frame = explodeFrame;
        if (frame < 0) frame = 0;
        if (frame > 3) frame = 3;
        sf::Sprite exSprite;
        exSprite.setTexture(Assets::snow_explode[frame]);
        sf::Vector2u sz = Assets::snow_explode[frame].getSize();
        float scale = 40.0f / (float)sz.x;
        exSprite.setScale(scale, scale);
        exSprite.setPosition(x - 20.0f, y - 20.0f);
        window.draw(exSprite);
        return;
    }

    // Draw rocket sprite
    sf::Sprite rocketSprite;
    rocketSprite.setTexture(Assets::gamakichi_rocket_t);
    sf::Vector2u sz = Assets::gamakichi_rocket_t.getSize();
    if (sz.x == 0 || sz.y == 0) {
        // Fallback: red circle if texture not loaded
        sf::CircleShape bomb(8.0f);
        bomb.setPosition(x, y);
        bomb.setFillColor(sf::Color::Red);
        window.draw(bomb);
        return;
    }
    float scale = 32.0f / (float)sz.y;
    rocketSprite.setScale(scale, scale);
    // Rotate to match velocity direction
    float angle = 0.0f;
    if (vx != 0.0f || vy != 0.0f) {
        angle = atan2(vy, vx) * 180.0f / 3.14159f;
    }
    rocketSprite.setRotation(angle);
    rocketSprite.setOrigin(sz.x / 2.0f, sz.y / 2.0f);
    rocketSprite.setPosition(x, y);
    window.draw(rocketSprite);
}

sf::FloatRect ArtilleryProjectile::getHitbox() const {
    return sf::FloatRect(x - 12.0f, y - 12.0f, 24.0f, 24.0f);
}
