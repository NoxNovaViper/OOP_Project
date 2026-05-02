#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Mogera : public Enemy {
private:
    bool movingRight;
    float spawnTimer;

public:
    Mogera(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    sf::FloatRect getHitbox() const override {
        return sf::FloatRect(x, y, 100.0f, 100.0f);
    }
};
