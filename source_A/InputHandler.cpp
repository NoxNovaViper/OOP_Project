#include "InputHandler.h"
void Inputhandle(Event& ev, Level_Manager& manager, RenderWindow& window, Player& p) {
    if ((manager.get_pause()) || (manager.get_transition())) {
		return;//if game state is paused or transitioning, thsi will not inputs
    }
    if (ev.type == sf::Event::KeyPressed) {
        switch (ev.key.code) {
        case Keyboard::Up: {
			jump(p.vy,p.jump_power,p.on_ground);
            break;
        }
        case Keyboard::Down: {
            fall(p.vy,p.y,p.on_ground);
            break;
        }
        case Keyboard::Left: {
            p_move(p.x,p.vx,2,true);
            break;
        }
        case Keyboard::Right: {
            p_move(p.x,-p.vx, 2, true);
            break;
        }
        case Keyboard::H: {
            manager.set_debug(!manager.get_debug());
            break;
        }
        case Keyboard::F1: {
			manager.set_debug(!manager.get_debug());
            break;
        }
        }
    }
    
}