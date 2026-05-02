#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
class Botom : public Enemy {
private:
    bool movingRight;
public:
    Botom(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
};
