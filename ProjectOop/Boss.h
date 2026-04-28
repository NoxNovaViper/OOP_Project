#pragma once
#include "Enemy.h"
class Boss : public Enemy {
protected:
    int maxhp;
    int phase;
    float phaseTimer;
    bool isdefeated;
    int gemReward;

public:
    Boss(float startX, float startY);
    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;
    virtual void hit() = 0;
    virtual void phaseChange() = 0;

    bool getIsDefeated() const {
        return isdefeated;
    }
    int collectGemReward() const {
        return gemReward;
    }
};