#include "LevelManager.h"
platform* Platform_Maker::create_platform(float x, float y, float w, float h) {
	platform* p = new platform;
	p->x = x;
	p->y = y;
	p->w = w;
	p->h = h;
	p->collison = FloatRect(x, y, w, h);
	return p;
}
float Platform_Maker::get_x(platform p) {
	return p.x;
}
float Platform_Maker::get_y(platform p) {
	return p.y;
}
float Platform_Maker::get_w(platform p) {
	return p.w;
}
float Platform_Maker::get_h(platform p) {
	return p.h;
}
void Level_Maker::create_level(int num_platforms, platform* platforms){
	l = new level;
	l->num_platforms = num_platforms;
	l->platforms = platforms;
}
Level_Maker::Level_Maker() {
	l = nullptr;
}
Level_Maker::~Level_Maker() {
	if(l!=nullptr){
		delete[] l->platforms;
		delete l;
		l = nullptr;
	}
}
Level_Manager::Level_Manager() {
	ifstream file("levels.txt");//stores the names of the files levels such as lev1.txt etc
	if (!file.is_open()) {
		cout << "File could not be opened" << endl;
		return;
	}
	string l;
	int c = 0;
	string* temp = nullptr;
	//Reads the file to store the level names
	while (getline(file, l)) {
		string* lev = new string[c + 1];
		for (int i = 0;i < c;i++) {
			lev[i] = temp[i];
		}
		lev[c] = l;
		c += 1;
		//delete old
		delete[] temp;
		//point to new
		temp = lev;
	}
		//initialize level data
	level_data = temp;
	temp = nullptr;
	//other initializations
	total_levels = c;
	s.play = false;
	s.pause = false;
	s.boss = false;
	s.mobs = false;
	s.transition = false;
	s.win = false;
	s.lose = false;
	s.debug = false;
}
void Level_Manager::next_level() {
	static int cur = -1;//current level
	cur += 1;//update level
	if (cur < total_levels) {
		ifstream file(level_data[cur]);
		int c;
		float x, y, w, h;
		file >> c;
		platform* next_p = new platform[c];
		for (int i = 0; i < c; i++) {
			file >> x >> y >> w >> h;
			next_p[i].x = x;
			next_p[i].y = y;
			next_p[i].w = w;
			next_p[i].h = h;
			next_p[i].collison = FloatRect(x, y, w, h);
		}
		levels.create_level(c, next_p);//level makercreates new level

		//play transition jump animation sound etc

		s.transition = false;//Transitioning to next level
		s.play = true;//player movement allowed
	}
	else {
		s.win = true;//Final win
	}
}
Level_Manager::~Level_Manager() {
	delete[] level_data;
}
void Level_Manager::set_debug(bool debug) {
	s.debug = debug;
}
void Level_Manager::set_play(bool play) {
	s.play = play;
}
void Level_Manager::set_pause(bool pause) {
	s.pause = pause;
}
void Level_Manager::set_boss(bool boss) {
	s.boss = boss;
}
void Level_Manager::set_mobs(bool mobs) {
	s.mobs = mobs;
}
void Level_Manager::set_transition (bool transition) {
	s.transition = transition;
}
void Level_Manager::set_win(bool win) {
	s.win = win;
}
void Level_Manager::set_lose(bool lose) {
	s.lose = lose;
}
bool Level_Manager::get_debug() {
	return s.debug;
}
bool Level_Manager::get_play() {
	return s.play;
}
bool Level_Manager::get_pause() {
	return s.pause;
}
bool Level_Manager::get_boss() {
	return s.boss;
}
bool Level_Manager::get_mobs() {
	return s.mobs;
}
bool Level_Manager::get_transition() {
	return s.transition;
}
bool Level_Manager::get_win() {
	return s.win;
}
bool Level_Manager::get_lose() {
	return s.lose;
}