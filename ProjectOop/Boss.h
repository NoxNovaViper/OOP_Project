#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
class Boss : public Enemy {
protected:
    int maxhp;
    int phase;
    float phaseTimer;
    bool isdefeated;
    int gemReward;
    bool right;
public:
    Boss(float startX, float startY);
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hit() = 0;
    virtual void phaseChange() = 0;

    bool getIsDefeated() const {
        return isdefeated;
    }
    int collectGemReward() const {
        return gemReward;
    }
};