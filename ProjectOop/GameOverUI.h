#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class GameOverScreen {
private:
    Texture bgTx;
    Sprite  bgSp;

    Font font;
    RectangleShape background;
    Text titleText;
    Text scoreText;
    Text levelText;

    RectangleShape retryBtn;
    Text retryBtnText;

    RectangleShape menuBtn;
    Text menuBtnText;

    int choice;

public:
    GameOverScreen();
    void setup();
    void setData(int score, int level);
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    int getChoice() { return choice; }
};