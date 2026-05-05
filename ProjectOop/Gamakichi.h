#pragma once
#include "Boss.h"
#include <SFML/Graphics.hpp>

class Gamakichi : public Boss {
private:
    float attackTimer;
    float attackDuration;
    float jumpTimer;
    float jumpDuration;
    int projectileCount;
    bool armActive;
    int fireQueue;
    float fireDelayTimer;

public:
    Gamakichi(float startX, float startY);
    void update(float Time) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    void phaseChange() override;
    void fireArtillery(float xOffset = 0.0f);

    sf::FloatRect getHitbox() const override {
        return sf::FloatRect(x, y, 100.0f, 100.0f);
    }

    float get_attack_timer() const;
    float get_attack_duration() const;
    int get_projectile_count() const;
    bool get_arm_active() const;
    void set_attack_timer(float t);
    void set_attack_duration(float d);
    void set_projectile_count(int c);
    void set_arm_active(bool a);
};