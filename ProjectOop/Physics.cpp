#include "Physics.h"
void jump(Player& p) {
	if (p.on_ground) {
		p.vy = -p.jump_power;
	}
}
void fall(Player& p, float len) {
	if (!p.on_ground) {
		p.vy = len;
	}
}
void p_move(Player& p, float speed, float t, bool horizontal) {
	Position_change(p, false, speed, t, horizontal);
}
void attack(Player& p) {
    // Placeholder for attack logic
}
void Gravity(Player& p, float g, float t) {
	p.vy = p.vy + (g * t);
}
void Position_change(Player& p, bool vertical, float v, float t, bool horizontal) {
	float cur_pos;
	if (vertical) { cur_pos = p.get_y(); }
	else { cur_pos = p.get_x(); }
	float new_pos = cur_pos + (v * t);

	if (horizontal) {
		if (new_pos > 800) { new_pos = 0; }
		else if (new_pos < 0) { new_pos = 800; }
	}

	if (vertical) {p.set_y(new_pos);}
	else {p.set_x(new_pos);}
}
float Position_check(float s, float v, float t) {
	return (s + (v * t));
}
bool collision_check(sf::FloatRect Player_hitbox, float y ,float v, float t, sf::FloatRect platform_hitbox) {
	sf::FloatRect new_pos = Player_hitbox;
	new_pos.top = Position_check(Player_hitbox.top, v, t);
	if (new_pos.intersects(platform_hitbox)) {
		if (v > 0) return true;
	}
	return false;
}
void Fix_collision(Player& p, float platform_top) {
	p.vy = 0;
	p.set_y(platform_top - player_h);
}
void debug_view(Level_Manager& manager,FloatRect Player_hitbox, platform* platforms, int num_platforms, RenderWindow& window) {
	if (manager.get_debug()) {
		RectangleShape debugBox;
		// Green for player hitbox
		debugBox.setPosition(Player_hitbox.left, Player_hitbox.top);
		debugBox.setSize(sf::Vector2f(Player_hitbox.width, Player_hitbox.height));
		debugBox.setOutlineColor(sf::Color::Green);
		debugBox.setOutlineThickness(2);
		debugBox.setFillColor(sf::Color::Transparent);
		window.draw(debugBox);
		//Platform colored outline blue
		debugBox.setOutlineColor(sf::Color::Blue);
		for (int i = 0; i < num_platforms; i++) {
			debugBox.setPosition(platforms[i].x, platforms[i].y);
			debugBox.setSize(sf::Vector2f(platforms[i].w, platforms[i].h));
			window.draw(debugBox);
		}
	}
}