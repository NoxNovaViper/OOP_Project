#include "Boss.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Mogera : public Boss {
private:
    bool movingRight;
    float spawnTimer;

public:
    void child_throw();
    void jump();
    void fall();
    void phaseChange() override;
    Mogera(float startX, float startY);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void hit() override;
    bool get_moving_right() const;
    float get_spawn_timer() const;
    void set_moving_right(bool new_moving_right);
    void set_spawn_timer(float new_spawn_timer);
    sf::FloatRect getHitbox() const override {
        float size = get_rolling() ? 100.0f * get_roll_scale() : 100.0f;
        return sf::FloatRect(x, y, size, size);
    }
};
