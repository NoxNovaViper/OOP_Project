#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Snowball : public Projectile {
private:
    float range;
    float distanceCovered;
    bool isRolling;
    int chainCount;

    float lifetime;//duration of existence
    float vy;//arc vertical

public:
    CircleShape ball;

    Snowball(float startX, float startY, float dirX);
    void update(float deltaTime) override;
    void draw(RenderWindow& w);
    void startRolling();
    int getChainCount() const {
        return chainCount;
    }

};