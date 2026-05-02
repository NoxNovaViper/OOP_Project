#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class ArtilleryProjectile : public Projectile {
private:
    float vy;
    float vx;
    bool is_hit;
public:

    ArtilleryProjectile(float startX, float startY, float startVx, float startVy);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
