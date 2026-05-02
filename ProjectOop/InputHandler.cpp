#include "InputHandler.h"
void Inputhandle(sf::Event& ev, Level_Manager& manager, sf::RenderWindow& window, Player& p1, Player& p2, Projectile** projectiles, int& count) {
    if ((manager.get_pause()) || (manager.get_transition())) {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
            manager.set_pause(false);
        }
        return;
    }

    if (ev.type == Event::KeyPressed) {
        switch (ev.key.code) {
            // Player 1 Controls
            case sf::Keyboard::W: jump(p1); break;
            case sf::Keyboard::S: fall(p1, p1.get_speed()); break;
            case sf::Keyboard::Space: attack(p1, projectiles, count); break;
            case sf::Keyboard::J: attack(p1, projectiles, count); break;

            // Player 2 Controls
            case sf::Keyboard::Numpad8: jump(p2); break;
            case sf::Keyboard::Numpad5: fall(p2, p2.get_speed()); break;
            case sf::Keyboard::Numpad0: attack(p2, projectiles, count); break;

            // System Controls
            case sf::Keyboard::Escape: manager.set_pause(!manager.get_pause()); break;
            case sf::Keyboard::F1: manager.set_debug(!manager.get_debug()); break;
            case sf::Keyboard::H: manager.set_debug(!manager.get_debug()); break;
            case sf::Keyboard::N: {
                manager.next_level(); 
				manager.set_next_level(true);
                break;
            }
            
            default: break;
        }
    }
}