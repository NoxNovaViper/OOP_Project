#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
using namespace std;
using namespace sf;
struct platform {
	float x;//position of the shape via top left corner
	float y;//y position 
	float w;//width
	float h;//height
	FloatRect collison;
};
struct state{
	bool play;
	bool pause;
	bool boss;
	bool mobs;
	bool transition;
	bool win;
	bool lose;
	bool debug;
};
struct level {
	int num_platforms;
	platform* platforms;
};
class Platform_Maker {
public:
	platform* create_platform(float x, float y, float w, float h);
	float get_x(platform p);
	float get_y(platform p);
	float get_w(platform p);
	float get_h(platform p);

};
class Level_Maker {
private:
	level* l;
public:
	void create_level(int num_platforms, platform* platforms);
	Level_Maker();
	~Level_Maker();
	level* get_level();
	
};
class Level_Manager {
	Level_Maker levels;
	string* level_data;
	state s;
	int total_levels;
public:
	Level_Manager();
	void next_level();
	~Level_Manager();
	level* get_current_level();
	void set_debug(bool debug);
	void set_play(bool play);
	void set_pause(bool pause);
	void set_boss(bool boss);
	void set_mobs(bool mobs);
	void set_transition(bool transition);
	void set_win(bool win);
	void set_lose(bool lose);
	bool get_debug();
	bool get_play();
	bool get_pause();
	bool get_boss();
	bool get_mobs();
	bool get_transition();
	bool get_win();
	bool get_lose();
};