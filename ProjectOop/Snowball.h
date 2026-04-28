#pragma once
#include "Projectile.h"
class Snowball : public Projectile {
private:
    float range;
    float distanceCovered;
    bool isRolling;
    int chainCount;

public:
    Snowball(float startX, float startY, float dirX);
    void update(float deltaTime) override;
    void draw() override;
    void startRolling();
    int getChainCount() const {
        return chainCount;
    }
};