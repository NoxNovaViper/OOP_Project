#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>
class Knife : public Projectile {
private:
    float damage;
public:
    Knife(float startX, float startY, float targetX, float targetY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};