#include "Physics.h"
#include "AssetLoader.h"
int snow::count = 0;

void snow::update(float time) {
	float move = dx * time * dir;
	x += move;
	dy += 450.0f * time;
	y += dy * time;
	distanceTraveled += std::abs(move);

	if (x < 0) {
		x = 800;
	}
	if (x > 800) {
		x = 0;
	}
	if (distanceTraveled >= maxDistance) {
		isactive = false;
	}
	if (y > Ground) {
		isactive = false;
	}
}
snow::snow(Player& p) {
	x = p.get_x();
	if (p.right_facing) {
		x += 15;
		dir = 1;
	}
	else {
		x -= 15;
		dir = -1;
	}
	y = p.get_y() + 15;
	dy = -80.0f; 
	dx = 300.0f; 
	distanceTraveled = 0.0f;
	maxDistance = p.get_snowballDistance();
	isactive = true;
	ball.setRadius(5);
	ball.setFillColor(Color::White);
	snow::count++;
}
snow::~snow() {
	snow::count--;
}
void snow::draw(RenderWindow& window) {
	if (Assets::snow_attack_t.getSize().x > 0 && Assets::snow_attack_t.getSize().y > 0) {
		Sprite snowSprite;
		snowSprite.setTexture(Assets::snow_attack_t);
		snowSprite.setPosition(x, y);
		snowSprite.setScale(16.0f / Assets::snow_attack_t.getSize().x, 16.0f / Assets::snow_attack_t.getSize().y);
		window.draw(snowSprite);
	}
	else {
		ball.setPosition(x, y);
		window.draw(ball);
	}
}
FloatRect snow::getHitbox() const {
	return FloatRect(x, y, 10.0f, 10.0f);
}

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
void attack(Player& p, Projectile** projectiles, int& projectile_count) {
	if (projectile_count < 30 && snow::count < 30) { // Use static count for limit
		projectiles[projectile_count] = new snow(p);
		projectile_count++;
		p.set_pushAnimTimer(0.25f);
	}
}
void Gravity(Player& p, float g, float t) {
	p.vy = p.vy + (g * t);
}
void Position_change(Player& p, bool vertical, float v, float t, bool horizontal) {
	float cur_pos;
	if (vertical) { 
		cur_pos = p.get_y();
	}
	else { 
		cur_pos = p.get_x();
	}
	float new_pos = cur_pos + (v * t);

	if (horizontal) {
		if (new_pos > 800) { 
			new_pos = 0;
		}
		else if (new_pos < 0) { 
			new_pos = 800;
		}
	}

	if (vertical) {p.set_y(new_pos);}
	else {p.set_x(new_pos);}
}
float Position_check(float s, float v, float t) {
	return (s + (v * t));
}
bool collision_check(FloatRect Player_hitbox, float y ,float v, float t, FloatRect platform_hitbox) {
	FloatRect new_pos = Player_hitbox;
	new_pos.top = Position_check(Player_hitbox.top, v, t);
	if (new_pos.intersects(platform_hitbox)) {
		if (v > 0) {
			return true;
		}
	}
	return false;
}
void Fix_collision(Player& p, float platform_top) {
	p.vy = 0;
	p.set_y(platform_top - player_h);
}
void debug_view(Level_Manager& manager,FloatRect Player_hitbox, platform* platforms, int num_platforms, RenderWindow& window) {
	if (manager.get_debug()) {
		draw_debug_box(window, Player_hitbox, sf::Color::Green);
		//Platform colored outline blue
		for (int i = 0; i < num_platforms; i++) {
			draw_debug_box(window, platforms[i].collison, sf::Color::Blue);
		}
	}
}
void draw_debug_box(RenderWindow& window, FloatRect hitbox, Color color) {
	RectangleShape debugBox;
	debugBox.setPosition(hitbox.left, hitbox.top);
	debugBox.setSize(sf::Vector2f(hitbox.width, hitbox.height));
	debugBox.setOutlineColor(color);
	debugBox.setOutlineThickness(2);
	debugBox.setFillColor(sf::Color::Transparent);
	window.draw(debugBox);
}
