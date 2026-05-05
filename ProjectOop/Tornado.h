#pragma once
#include <SFML/Graphics.hpp>
#include "FlyngFoogaFoog.h"
class Tornado : public FlyngFoogafoog {
private:
    float knifeTimer;
    float knifeDuration;
    float flyspeedrandomly;

public:
    Tornado(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    void knifeThrow();
    void kill() override;
    float get_knife_timer() const;
    float get_knife_duration() const;
    float get_fly_speed_randomly() const;
    void set_knife_timer(float new_knife_timer);
    void set_knife_duration(float new_knife_duration);
    void set_fly_speed_randomly(float new_fly_speed_randomly);
};
