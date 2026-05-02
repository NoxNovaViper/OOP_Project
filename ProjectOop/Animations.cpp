#include "Animations.h"
#include <iostream>
#include "AssetLoader.h"
void load_assets(Player& p) {
    float w = 48.0f;
    float h = 48.0f;
	p.get_sprite().setTexture(Assets::idle, true);
	p.get_sprite().setScale(
		w / Assets::idle.getSize().x,
		h / Assets::idle.getSize().y
	);
	p.get_sprite().setOrigin(Assets::idle.getSize().x / 2.0f, Assets::idle.getSize().y / 2.0f);
}
void update_animations(Player& p, float Time, bool left, bool right) {
	static float timers[3] = {0, 0, 0};//
	const float dura = 0.15f;
	int Frames = 4;
	if (!p.on_ground) {
		Frames = 6;
	}
	int p_num = p.get_playerNumber();
	if ((p_num < 1) || (p_num > 2)) { 
		p_num = 1;
	}
	bool moving = left || right;
    float pushTimer = p.get_pushAnimTimer();
    if (pushTimer > 0.0f) {
        pushTimer -= Time;
        if (pushTimer < 0.0f) {
            pushTimer = 0.0f;
        }
        p.set_pushAnimTimer(pushTimer);
    }
	if (moving) {
		timers[p_num] += Time;
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

    if (!p.get_isalive()) {
        int frame = p.get_cur_frame() % 4;
        p.get_sprite().setTexture(Assets::death[frame], true);
    } else if (pushTimer > 0.0f) {
        int frame = p.get_cur_frame() % 4;
        p.get_sprite().setTexture(Assets::push[frame], true);
    } else if (!p.get_on_ground()) {
        if (p.get_vy() < 0) {
            //jump
            int frame = p.get_cur_frame() % 6;
            p.get_sprite().setTexture(Assets::jump[frame], true);
        } else {
            //fall
            p.get_sprite().setTexture(Assets::fall[0], true);
        }
    } else if (moving) {
        //walk
        int frame = p.get_cur_frame() % 4;
        p.get_sprite().setTexture(Assets::walk[frame], true);
    } else {
        //idle
        p.get_sprite().setTexture(Assets::idle, true);
    }

	float w = 48.0f;
	float h = 48.0f;
    float scaleX, scaleY;
    
    //bound safety check
    if (p.get_sprite().getTexture() != nullptr) {
	    scaleX = w / p.get_sprite().getTexture()->getSize().x;
	    scaleY = h / p.get_sprite().getTexture()->getSize().y;
	    p.get_sprite().setOrigin(p.get_sprite().getTexture()->getSize().x / 2.0f, p.get_sprite().getTexture()->getSize().y / 2.0f);
    } else {
        scaleX = 1.0f; scaleY = 1.0f;
    }

	if (right) {
		p.get_sprite().setScale(-scaleX, scaleY);
	} else {
		p.get_sprite().setScale(scaleX, scaleY);
	}
	//sprite hitbox centering
	p.get_sprite().setPosition(p.get_x() + 15.0f, p.get_y() + 25.0f);
}
