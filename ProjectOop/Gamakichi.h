#pragma once
#include "Boss.h"
class Gamakichi : public Boss {
private:
    float attackTimer;
    float attackDuration;
    int projectileCount;
    bool armActive;

public:
    Gamakichi(float startX, float startY);
    void update(float deltaTime) override;
    void draw() override;
    void hit() override;
    void phaseChange() override;
    void fireArtillery();
};