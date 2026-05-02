#pragma once
#include <SFML/Graphics.hpp>
#include "FlyngFoogaFoog.h"
class Tornado : public FlyngFoogafoog {
private:
    float knifeTimer;
    float knifeDuration;
    float flyspeedrandomly;

public:
    Tornado(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    void knifeThrow();
    void kill() override;
};