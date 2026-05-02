#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Projectile {
protected:
    float x, y;
    float speedX, speedY;
    bool isactive;
    Sprite sprite;
    Texture texture;
    FloatRect hitbox;

public:
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Projectile() {}
    virtual sf::FloatRect getHitbox() const {
        return sf::FloatRect(x, y, 16.0f, 16.0f);
    }

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
