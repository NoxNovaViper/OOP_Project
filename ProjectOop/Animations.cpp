#include "Animations.h"
#include <iostream>
void load_assets(Player& p) {
    float w = 48.0f;
    float h = 48.0f;
    string link = "C:/Users/HP/source/repos/ProjectOop/ProjectOop/SnowBrosAssets/" + p.get_name() + "_sprites/walk_01.png";
    if (!p.get_texture().loadFromFile(link)) {
        p.get_texture().loadFromFile("C:/Users/HP/source/repos/ProjectOop/ProjectOop/SnowBrosAssets/Nick_sprites/walk_01.png");
    }
	p.get_sprite().setTexture(p.get_texture(), true);
	p.get_sprite().setScale(
		w / p.get_texture().getSize().x,
		h / p.get_texture().getSize().y
	);
	p.get_sprite().setOrigin(0, 0);
}
void update_animations(Player& p, float deltaTime, bool left, bool right) {
	static float timers[3] = {0, 0, 0};
	const float dura = 0.15f;
	int Frames = 4;
	if (!p.on_ground) {
		Frames = 6;
	}
	int p_num = p.get_playerNumber();
	if ((p_num < 1) || (p_num > 2)) { p_num = 1; }

	bool is_moving = left || right;

	if (is_moving) {
		timers[p_num] += deltaTime;
		if (timers[p_num] >= dura) {
			timers[p_num] = 0;
			p.set_cur_frame((p.get_cur_frame() + 1) % Frames);
		}
	} else {
		timers[p_num] = 0;
		p.set_cur_frame(0);
	}

	string frame_num;
	if (p.get_cur_frame() + 1 < 10) {
		frame_num = "0";
	}
	else {
		frame_num = "";
	}
	frame_num += to_string(p.get_cur_frame() + 1);

        string curr_action = "walk";
        if (!p.get_on_ground()) {
            if (p.get_vy() < 0) 
            { curr_action = "jump"; }
            else { curr_action = "fall"; }
        }
        string link = "C:/Users/HP/source/repos/ProjectOop/ProjectOop/SnowBrosAssets/" + p.get_name() + "_sprites/" + curr_action + "_" + frame_num + ".png";

	if (!p.get_texture().loadFromFile(link)) {
		p.get_texture().loadFromFile("C:/Users/HP/source/repos/ProjectOop/ProjectOop/SnowBrosAssets/Nick_sprites/walk_01.png");
	}

	p.get_sprite().setTexture(p.get_texture(), true);

	float w = 48.0f;
	float h = 48.0f;
	float scaleX = w / p.get_texture().getSize().x;
	float scaleY = h / p.get_texture().getSize().y;

	if (right) {
		p.get_sprite().setScale(-scaleX, scaleY);
		p.get_sprite().setOrigin(p.get_texture().getSize().x, 0);
	} else if (left) {
		p.get_sprite().setScale(scaleX, scaleY);
		p.get_sprite().setOrigin(0, 0);
	} else {
		if (p.get_sprite().getScale().x < 0) {
			p.get_sprite().setScale(-scaleX, scaleY);
			p.get_sprite().setOrigin(p.get_texture().getSize().x, 0);
		} else {
			p.get_sprite().setScale(scaleX, scaleY);
			p.get_sprite().setOrigin(0, 0);
		}
	}
	p.get_sprite().setPosition(p.get_x(), p.get_y());
}
