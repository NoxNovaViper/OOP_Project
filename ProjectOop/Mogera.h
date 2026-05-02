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
        float size = get_rolling() ? 100.0f * get_roll_scale() : 100.0f;
        return sf::FloatRect(x, y, size, size);
    }
};
