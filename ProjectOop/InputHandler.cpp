#include "InputHandler.h"
using namespace sf;
using namespace std;
void Inputhandle(Event& ev, Level_Manager& manager, RenderWindow& window, Player& p1, Player& p2, Projectile** projectiles, int& count) {
    if ((manager.get_pause()) || (manager.get_transition())) {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == Keyboard::Escape) {
            manager.set_pause(false);
        }
        return;
    }

    if (ev.type == Event::KeyPressed) {
        switch (ev.key.code) {
            // Player 1 Controls
            case Keyboard::W: jump(p1); break;
            case Keyboard::S: fall(p1, p1.get_speed()); break;
            case Keyboard::Space: attack(p1, projectiles, count); break;
            case Keyboard::J: attack(p1, projectiles, count); break;

            // Player 2 Controls
            case Keyboard::Numpad8: jump(p2); break;
            case Keyboard::Numpad5: fall(p2, p2.get_speed()); break;
            case Keyboard::Numpad0: attack(p2, projectiles, count); break;

            // System Controls
            case Keyboard::Escape: manager.set_pause(!manager.get_pause()); break;
            case Keyboard::F1: manager.set_debug(!manager.get_debug()); break;
            case Keyboard::H: manager.set_debug(!manager.get_debug()); break;
            
            default: break;
        }
    }
}