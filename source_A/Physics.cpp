#include "Physics.h"
void jump(float& v, float len, bool on_ground) {
	if (on_ground) {
		v = -len;//since 0 is highest and 600 lowest
	}
}
void fall(float& v, float len, bool on_ground) {
	if (!on_ground) {
		v = len;//since 0 is highest and 600 lowest
	}
}
void p_move(float len, float sp, float t, bool h) {
	Position_change(len, sp, t, h);//move player by changing their position based on the speed and time
}
void attack();
void Gravity(float& v, float g, float t) {
	v = v + (g * t);//v=u+at
}
void Position_change(float& s, float v, float t, bool h) {
	s = s + (v * t);//s=s+vt
	if (h) {//in case of horizontal movement
		if (s > 800) {
			s = 0;// to warp around the screen
		}
		else if (s < 0) {//backwards warp
			s = 800;
		}
	}
}
//helper to predict future position
float Position_check(float s, float v, float t) {
	return (s + (v * t));//s=s+vt
}
bool collision_check(FloatRect Player_hitbox, float y ,float v, float t, FloatRect platform_hitbox) {
	FloatRect new_pos = Player_hitbox;
	new_pos.top = Position_check(Player_hitbox.top, v, t);//predicted platform hitbox for collision checking
	//main bottom check
	if (new_pos.intersects(platform_hitbox)) {
		if ((v > 0) && (new_pos.intersects(platform_hitbox))) {
			//if player is falling and predicted hitbox intersects platform
			return true;
		}
	}
	return false;
}
void Fix_collision(float& y_pos, float& v, float platform_top) {
	v = 0;//stop player movement
	y_pos = platform_top - player_h;
	//place player on top of platform as player height is subtracted from the bottom
}//Enimies logic Attack and movement will be implemented in the future, but for now they are just placeholders.
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