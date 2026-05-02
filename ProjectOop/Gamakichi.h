#pragma once
#include "Boss.h"
#include <SFML/Graphics.hpp>
class Gamakichi : public Boss {
private:
    float attackTimer;
    float attackDuration;
    int projectileCount;
    bool armActive;
    
public:
    Gamakichi(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    sf::FloatRect getHitbox() const override {
        return sf::FloatRect(x, y, 100.0f, 100.0f);
    }
    void phaseChange() override;
    void fireArtillery();
    float get_attack_timer() const;
    float get_attack_duration() const;
    int get_projectile_count() const;
    bool get_arm_active() const;
    void set_attack_timer(float new_attack_timer);
    void set_attack_duration(float new_attack_duration);
    void set_projectile_count(int new_projectile_count);
    void set_arm_active(bool new_arm_active);
};
