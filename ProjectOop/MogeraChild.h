#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class MogeraChild : public Enemy {
private:
    float directionX;

public:
    MogeraChild(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    float get_direction_x() const;
    void set_direction_x(float new_direction_x);
    FloatRect getHitbox() const override {
        float size = get_rolling() ? 20.0f * get_roll_scale() : 20.0f;
        return FloatRect(x, y, size, size);//child hitbox defined
    }
};
