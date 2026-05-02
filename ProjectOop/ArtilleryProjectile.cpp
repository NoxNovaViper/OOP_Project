#include "ArtilleryProjectile.h"
#include "AssetLoader.h" // assuming some asset for projectile

ArtilleryProjectile::ArtilleryProjectile(float startX, float startY, float startVx, float startVy) {
    x = startX;
    y = startY;
    vx = startVx;
    vy = startVy;
    isactive = true;
    is_hit = false;
}

void ArtilleryProjectile::update(float deltaTime) {
    if (!isactive) return;
    
    // Arc movement
    vy += 400.0f * deltaTime; // gravity
    
    x += vx * deltaTime;
    y += vy * deltaTime;
    
    // If it hits the floor, explode
    if (y >= 500.0f) {
        y = 500.0f;
        isactive = false; // "explode" and disappear for now
    }
}

void ArtilleryProjectile::draw(sf::RenderWindow& window) {
    sf::CircleShape bomb(8.0f);
    bomb.setPosition(x, y);
    bomb.setFillColor(sf::Color::Red);
    window.draw(bomb);
}
