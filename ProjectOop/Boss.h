#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
class Boss : public Enemy {
protected:
    int max_hp;
    int phase;
    float phase_timer;
    bool is_defeated;
    int gem_reward;
    bool right;


public:
    Boss(float startX, float startY);
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hit() = 0;
    virtual void phaseChange() = 0;

    bool get_is_defeated() const {
        return is_defeated;
    }
    int collect_gem_reward() const {
        return gem_reward;
    }
    int get_max_hp() const {
        return max_hp;
    }
    int get_phase() const {
        return phase;
    }
    float get_phase_timer() const {
        return phase_timer;
    }
    int get_gem_reward() const {
        return gem_reward;
    }
    bool get_right() const {
        return right;
    }
    void set_max_hp(int new_max_hp) {
        max_hp = new_max_hp;
    }
    void set_phase(int new_phase) {
        phase = new_phase;
    }
    void set_phase_timer(float new_phase_timer) {
        phase_timer = new_phase_timer;
    }
    void set_is_defeated(bool new_is_defeated) {
        is_defeated = new_is_defeated;
    }
    void set_gem_reward(int new_gem_reward) {
        gem_reward = new_gem_reward;
    }
    void set_right(bool new_right) {
        right = new_right;
    }
};
