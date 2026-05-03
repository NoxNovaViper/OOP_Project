#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
class Boss : public Enemy {
protected:
    int maxhp;
    int phase;
    float phaseTimer;
    bool isdefeated;
    int gemReward;
    bool right;


public:
    Boss(float startX, float startY);
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hit() = 0;
    virtual void phaseChange() = 0;

    bool getIsDefeated() const {
        return isdefeated;
    }
    int collectGemReward() const {
        return gemReward;
    }
    int get_max_hp() const {
        return maxhp;
    }
    int get_phase() const {
        return phase;
    }
    float get_phase_timer() const {
        return phaseTimer;
    }
    int get_gem_reward() const {
        return gemReward;
    }
    bool get_right() const {
        return right;
    }
    void set_max_hp(int new_max_hp) {
        maxhp = new_max_hp;
    }
    void set_phase(int new_phase) {
        phase = new_phase;
    }
    void set_phase_timer(float new_phase_timer) {
        phaseTimer = new_phase_timer;
    }
    void set_is_defeated(bool new_is_defeated) {
        isdefeated = new_is_defeated;
    }
    void set_gem_reward(int new_gem_reward) {
        gemReward = new_gem_reward;
    }
    void set_right(bool new_right) {
        right = new_right;
    }
};
