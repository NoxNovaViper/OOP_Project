#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class LevelCompleteScreen {
private:
    Font font;
    RectangleShape background;
    Text titleText;
    Text scoreText;
    Text gemsText;

    RectangleShape nextBtn;
    Text nextBtnText;

    int choice;
    Texture bgTx;
    Sprite  bgSp;

public:
    LevelCompleteScreen();
    void setup();
    void setData(int score, int gems);
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    int getChoice() { return choice; }
};