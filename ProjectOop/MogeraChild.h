#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
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
    FloatRect getHitbox() const override {
        float size = get_rolling() ? 20.0f * get_roll_scale() : 20.0f;
        return FloatRect(x, y, size, size);//child hitbox defined
    }
};
