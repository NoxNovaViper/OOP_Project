#pragma once
#include"Enemy.h"
class Botom : public Enemy {
private:

    bool movingRight;

public:
    Botom(float startX, float startY);
    void update(float deltaTime) override;
    void draw() override;
    void hit() override;
};
