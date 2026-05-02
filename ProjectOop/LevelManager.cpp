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
void Level_Maker::create_level(int num_platforms, platform* platforms, int num_enemies, enemy_spawn* enemies) {
	if (l != nullptr) {
		delete[] l->platforms;
		if (l->enemies != nullptr) {
			delete[] l->enemies;
		}
		delete l;
	}
	l = new level;
	l->num_platforms = num_platforms;
	l->platforms = platforms;
	l->num_enemies = num_enemies;
	l->enemies = enemies;
}
Level_Maker::Level_Maker() {
	l = nullptr;
}
Level_Maker::~Level_Maker() {
	if (l != nullptr) {
		delete[] l->platforms;
		if (l->enemies != nullptr) {
			delete[] l->enemies;
		}
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
		if (!l.empty() && l.back() == '\r') l.pop_back();
		if (l.empty()) continue;
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
	s.start_screen = true;
	s.login = false;
	s.character_select = false;
	s.play = false;
	s.pause = false;
	s.boss = false;
	s.mobs = false;
	s.transition = false;
	s.win = false;
	s.lose = false;
	s.debug = false;
	s.next_level = false;
}
void Level_Manager::next_level() {
	static int cur = -1;//current level
	cur += 1;//update level
	if (cur < total_levels) {
		string filename = level_data[cur];
		// Sanitize string to remove any hidden carriage returns or trailing spaces manually (no algorithm library)
		string clean_filename = "";
		for (int i = 0; i < filename.length(); i++) {
			char c = filename[i];
			if (c != '\r' && c != '\n' && c != ' ' && c != '\t') {
				clean_filename += c;
			}
		}
		ifstream file(clean_filename);
		if (!file.is_open()) {
			cout << "Failed to open level file: " << clean_filename << endl;
			return;
		}
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
		int e_count = 0;
		if (file >> e_count) {
			enemy_spawn* next_e = nullptr;
			if (e_count > 0) {
				next_e = new enemy_spawn[e_count];
				for (int i = 0; i < e_count; i++) {
					file >> next_e[i].type >> next_e[i].x >> next_e[i].y;
				}
			}
			levels.create_level(c, next_p, e_count, next_e);//level makercreates new level
		} else {
			levels.create_level(c, next_p, 0, nullptr);//fallback if no enemies in file
		}

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
void Level_Manager::set_start_screen(bool start_screen) {
	s.start_screen = start_screen;
}
void Level_Manager::set_login(bool login) {
	s.login = login;
}
void Level_Manager::set_character_select(bool character_select) {
	s.character_select = character_select;
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
void Level_Manager::set_transition(bool transition) {
	s.transition = transition;
}
void Level_Manager::set_win(bool win) {
	s.win = win;
}
void Level_Manager::set_lose(bool lose) {
	s.lose = lose;
}
void Level_Manager::set_next_level(bool next_level) {
	s.next_level = next_level;
}
void Level_Manager::set_main_menu(bool m) {
	s.main_menu = m;
}
bool Level_Manager::get_start_screen() {
	return s.start_screen;
}
bool Level_Manager::get_login() {
	return s.login;
}
bool Level_Manager::get_character_select() {
	return s.character_select;
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
bool Level_Manager::get_next_level() {
	return s.next_level;
}
bool Level_Manager::get_main_menu() {
	return s.main_menu;
}

// In Level_Maker
level* Level_Maker::get_level() { 
	return l;
}
// In Level_Manager
level* Level_Manager::get_current_level() { 
	return levels.get_level();
}
