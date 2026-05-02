#include "Enemy_AI.h"
bool search(int player_x, int enemy_x, int player_y, int enemy_y) {
	if ((abs(player_x - enemy_x) < 50) && (abs(player_y - enemy_y) <= 5)) {
		return true;
	}
	return false;
}
void update_fireball(CircleShape& fireball, bool& active, FloatRect player_hitbox) {
    if (!active) {
        return;
    }
    fireball.move(2.0f, 0.0f);
    if (fireball.getGlobalBounds().intersects(player_hitbox)) {
        active = false;
    }
    if (fireball.getPosition().x > 800) {
        active = false;
    }
}
void frozen(){

}
void defrost() {
	//plays defrost animation
}
