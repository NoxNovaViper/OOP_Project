#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
protected:
    float x, y;
    float speedX, speedY;
    bool isactive;

public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Projectile() {}

    bool getisactive() const {
        return isactive;
    }
    void setisactive(bool val) {
        isactive = val;
    }
    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
};