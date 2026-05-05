#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class LevelCompleteScreen {
private:
    Font font;
    RectangleShape background;
    Text title_text;
    Text score_text;
    Text gems_text;

    RectangleShape next_btn;
    Text next_btn_text;

    int choice;
    Texture bg_tx;
    Sprite  bg_sp;

public:
    LevelCompleteScreen();
    void set_up();
    void set_data(int score, int gems);
    void handle_input(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    int get_choice() { return choice; }
};