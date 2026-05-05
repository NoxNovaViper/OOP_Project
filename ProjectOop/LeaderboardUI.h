#pragma once
#include <SFML/Graphics.hpp>
#include "Database.h"
#include <string>
using namespace std;
using namespace sf;

class LeaderboardUI {
private:
    Font font;
    Texture bg_tx;
    Sprite bg_sp;
    Text title;
    Text column_headers;
    Text entries[10];
    RectangleShape back_btn;
    Text back_text;
    bool is_open;

    string usernames[100];
    int scores[100];
    int levels[100];
    int count;

public:
    LeaderboardUI();
    void set_up();
    void load_data(Database& database);
    void handle_input(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);
    bool get_is_open() const { return is_open; }
    void set_open(bool open) { is_open = open; }
};
