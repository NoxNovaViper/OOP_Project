#include "Animations.h"
#include <iostream>
#include "AssetLoader.h"
void load_assets(Player& p) {
    float w = 48.0f;
    float h = 48.0f;
	p.get_sprite().setTexture(Assets::idle[0], true);
	p.get_sprite().setScale(
		w / Assets::idle[0].getSize().x,
		h / Assets::idle[0].getSize().y
	);
	p.get_sprite().setOrigin(Assets::idle[0].getSize().x / 2.0f, Assets::idle[0].getSize().y / 2.0f);
}
void update_animations(Player& p, float Time, bool left, bool right) {
	static float anim_timers[3] = {0, 0, 0};//animation timers for players
	const float duration = 0.15f; //frame duration
	int frames = 4; //default frames
	if (!p.on_ground) {
		frames = 6;
	}
	int p_num = p.get_playerNumber();
	if ((p_num < 1) || (p_num > 2)) { 
		p_num = 1;
	}
	bool moving = left || right;
    float push_timer = p.get_pushAnimTimer();
    if (push_timer > 0.0f) {
        push_timer -= Time;
        if (push_timer < 0.0f) {
            push_timer = 0.0f;
        }
        p.set_pushAnimTimer(push_timer);
    }
    float throw_timer = p.get_throwAnimTimer();
    if (throw_timer > 0.0f) {
        throw_timer -= Time;
        if (throw_timer < 0.0f) {
            throw_timer = 0.0f;
        }
        p.set_throwAnimTimer(throw_timer);
    }

    //animation state machine
	if (throw_timer > 0.0f) {
		anim_timers[p_num] += Time;
		if (anim_timers[p_num] >= 0.05f) { // throw animation speed
			anim_timers[p_num] = 0;
			p.set_cur_frame((p.get_cur_frame() + 1) % 8);
		}
	} else if (moving) {
		anim_timers[p_num] += Time;
		if (anim_timers[p_num] >= duration) {
			anim_timers[p_num] = 0;
			p.set_cur_frame((p.get_cur_frame() + 1) % frames);
		}
	} else if (p.get_on_ground()) {
        // idle animation
		anim_timers[p_num] += Time;
		if (anim_timers[p_num] >= duration * 2.0f) {
			anim_timers[p_num] = 0;
			p.set_cur_frame((p.get_cur_frame() + 1) % 2);
		}
	} else {
        if (p.get_cur_frame() != 0) { // reset
            p.set_cur_frame(0);
            anim_timers[p_num] = 0;
        }
		anim_timers[p_num] = 0;
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

    int char_type = p.get_playerNumber(); // using playerNumber as char type for now, or add get_char_type
    // Map charactype (1=Blue/Nick, 2=Red/Tom, 3=Green/Bob)
    // Actually p.get_playerNumber() returns 1 or 2 for player slot.
    // I need the actual character type from Player class.
    // Let's assume we can get it.
    
    if (!p.get_isalive()) {
        //death animation
        int frame = p.get_cur_frame() % 7;
        if (p.get_name() == "Tom") p.get_sprite().setTexture(Assets::red_death[frame % 5], true);
        else if (p.get_name() == "Bob") p.get_sprite().setTexture(Assets::green_death[frame % 4], true);
        else p.get_sprite().setTexture(Assets::death[frame % 7], true);
    } else if (throw_timer > 0.0f) {
        //throw animation
        int frame = p.get_cur_frame() % 8;
        p.get_sprite().setTexture(Assets::throw_t[frame], true); // Throw is shared for now or needs frames
    } else if (push_timer > 0.0f) {
        //push animation
        int frame = p.get_cur_frame() % 3;
        p.get_sprite().setTexture(Assets::push[frame], true);
    } else if (!p.get_on_ground()) {
        //gravity and air state
        if (p.get_vy() < 0) {
            //jump
            int frame = p.get_cur_frame() % 6;
            if (p.get_name() == "Tom") p.get_sprite().setTexture(Assets::red_run[frame % 4], true); // red jump missing, use run
            else if (p.get_name() == "Bob") p.get_sprite().setTexture(Assets::green_jump[frame % 3], true);
            else p.get_sprite().setTexture(Assets::jump[frame % 6], true);
        } else {
            //fall
            if (p.get_name() == "Tom") p.get_sprite().setTexture(Assets::red_run[0], true);
            else if (p.get_name() == "Bob") p.get_sprite().setTexture(Assets::green_idle, true);
            else p.get_sprite().setTexture(Assets::fall[0], true);
        }
    } else if (moving) {
        //walk/run
        int frame = p.get_cur_frame() % 4;
        if (p.get_name() == "Tom") p.get_sprite().setTexture(Assets::red_run[frame], true);
        else if (p.get_name() == "Bob") p.get_sprite().setTexture(Assets::green_run[frame], true);
        else p.get_sprite().setTexture(Assets::walk[frame], true);
    } else {
        //idle
        int frame = p.get_cur_frame() % 2;
        if (p.get_name() == "Tom") p.get_sprite().setTexture(Assets::red_idle, true);
        else if (p.get_name() == "Bob") p.get_sprite().setTexture(Assets::green_idle, true);
        else p.get_sprite().setTexture(Assets::idle[frame % 2], true);
    }

	float width = 48.0f;
	float height = 48.0f;
    float scale_x, scale_y;
    
    //sprite scaling logic
    if (p.get_sprite().getTexture() != nullptr) {
	    scale_x = width / p.get_sprite().getTexture()->getSize().x;
	    scale_y = height / p.get_sprite().getTexture()->getSize().y;
	    p.get_sprite().setOrigin(p.get_sprite().getTexture()->getSize().x / 2.0f, p.get_sprite().getTexture()->getSize().y / 2.0f);
    } else {
        scale_x = 1.0f; scale_y = 1.0f;
    }

	if (right) {
		p.get_sprite().setScale(-scale_x, scale_y); //flip sprite
	} else {
		p.get_sprite().setScale(scale_x, scale_y);
	}
	//sprite position update
	p.get_sprite().setPosition(p.get_x() + 15.0f, p.get_y() + 25.0f);
}
