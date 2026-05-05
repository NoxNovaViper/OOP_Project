#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class PauseMenu {
private:
    Texture bg_tx;
    Sprite  bg_sp;

    Font font;
    RectangleShape background;
    Text title_text;

    RectangleShape resume_btn;
    Text resume_text;

    RectangleShape shop_btn;
    Text shop_text;

    RectangleShape save_btn;
    Text save_text;

    RectangleShape logout_btn;
    Text logout_text;

    RectangleShape exit_btn;
    Text exit_text;

    int choice;
    bool is_open;

public:
    PauseMenu();
    void set_up();
    void handle_input(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    void open() { is_open = true; }
    void close() { is_open = false; }
    bool get_is_open() { return is_open; }
    int get_choice() { return choice; }
    void reset_choice() { choice = 0; }
};