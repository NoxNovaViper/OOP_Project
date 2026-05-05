#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Mainmenu {
private:
    int choice;
    Texture bg_tx;
    Sprite bg_sp;
    Font font;
    RectangleShape background;
    Text title_text;

    // main buttons
    RectangleShape new_game_btn;
    Text new_game_text;
    RectangleShape continue_btn;
    Text continue_text;
    RectangleShape leaderboard_btn;
    Text leaderboard_text;
    RectangleShape exit_btn;
    Text exit_text;

    // mode select buttons
    bool show_mode_select;
    bool mode_selected;
    bool is_single_player;
    Text mode_title;
    RectangleShape single_btn;
    Text single_text;
    RectangleShape multi_btn;
    Text multi_text;

public:
    Mainmenu();
    void set_up();
    void handle_input(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);
    void reset_choice()
    {
        choice = 0;
        show_mode_select = false;
        mode_selected = false;
    }
    int get_choice() { return choice; }
    bool get_mode_selected() { return mode_selected; }
    bool get_is_single_player() { return is_single_player; }
};