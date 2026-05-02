#pragma once
#include "Boss.h"
#include <SFML/Graphics.hpp>
class Gamakichi : public Boss {
private:
    float attackTimer;
    float attackDuration;
    int projectileCount;
    bool armActive;
    
public:
    Gamakichi(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    sf::FloatRect getHitbox() const override {
        return sf::FloatRect(x, y, 100.0f, 100.0f);
    }
    void phaseChange() override;
    void fireArtillery();
};