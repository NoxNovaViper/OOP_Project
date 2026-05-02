#include "ArtilleryProjectile.h"
#include "AssetLoader.h"

ArtilleryProjectile::ArtilleryProjectile(float startX, float startY, float startVx, float startVy) {
    x = startX;
    y = startY;
    vx = startVx;
    vy = startVy;
    isactive = true;
    is_hit = false;
}

void ArtilleryProjectile::update(float Time) {
    if (!isactive) return;
    // Arc movement
    vy += 400.0f*Time;//gravity
    
    x += vx * Time;
    y += vy * Time;
    
    //Explode on touching floor
    if (y >= 500.0f) {
        y = 500.0f;
        isactive = false; //dissapera rn, will add logic later
    }
}

void ArtilleryProjectile::draw(RenderWindow& window) {
    CircleShape bomb(8.0f);
    bomb.setPosition(x, y);
    bomb.setFillColor(sf::Color::Red);
    window.draw(bomb);
}
