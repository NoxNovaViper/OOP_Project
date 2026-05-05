#pragma once
#include <SFML/Graphics.hpp>
#include "AssetLoader.h"

// base class for things spawned on enemy death
class spawnable {
protected:
    float x, y;
    bool active;
    sf::Sprite s;
public:
    spawnable(float _x, float _y) : x(_x), y(_y), active(true) {}
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    bool get_active() const { return active; }
    void set_active(bool a) { active = a; }
    sf::FloatRect get_hitbox() const { return s.getGlobalBounds(); }
    virtual ~spawnable() {}
};

// money drop for score
class money : public spawnable {
public:
    money(float _x, float _y) : spawnable(_x, _y) {
        s.setTexture(Assets::money_t);
        s.setPosition(x, y);
        s.setScale(30.0f / Assets::money_t.getSize().x, 30.0f / Assets::money_t.getSize().y);
    }
    void update(float dt) override {
        // gravity for money drops
        y += 150.0f * dt;
        if (y > 520.0f) {
            y = 520.0f;
        }
        s.setPosition(x, y);
    }
    void draw(sf::RenderWindow& window) override {
        window.draw(s);
    }
};

// powerup drop
class powerup : public spawnable {
private:
    int type;
public:
    powerup(float _x, float _y, int t) : spawnable(_x, _y), type(t) {
        s.setTexture(Assets::sushi[type % 5]);
        s.setPosition(x, y);
        s.setScale(30.0f / Assets::sushi[type % 5].getSize().x, 30.0f / Assets::sushi[type % 5].getSize().y);
    }
    void update(float dt) override {
        y += 150.0f * dt;
        if (y > 520.0f) {
            y = 520.0f;
        }
        s.setPosition(x, y);
    }
    void draw(sf::RenderWindow& window) override {
        window.draw(s);
    }
    int get_type() const { return type; }
};
