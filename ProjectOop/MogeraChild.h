#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class MogeraChild : public Enemy {
private:
    float vy;
    bool on_ground;
    float directionX;

public:
    MogeraChild(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    sf::FloatRect getHitbox() const override {
        return sf::FloatRect(x, y, 20.0f, 20.0f);
    }
};
