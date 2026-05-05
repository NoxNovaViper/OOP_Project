#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class CharacterSelect {
private:
    Font font;
    RectangleShape background;
    Text title_text;
    Text instruction_text;
    Texture bg_tx;
    Sprite  bg_sp;

    // nick button
    RectangleShape nick_btn;
    Text nick_text;
    Text nick_stats;

    // tom button
    RectangleShape tom_btn;
    Text tom_text;
    Text tom_stats;

    // custom button
    RectangleShape custom_btn;
    Text custom_text;
    Text custom_stats;

    // images
    Texture nick_tex;
    Texture tom_tex;
    Texture custom_tex;
    Sprite nick_sprite;
    Sprite tom_sprite;
    Sprite custom_sprite;

    int choice;
    bool selection_done;

public:
    CharacterSelect();
    void set_up(int player_number);
    void handle_input(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    bool get_selection_done() { return selection_done; }
    int get_choice() { return choice; }
};