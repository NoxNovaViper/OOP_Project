#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class BossDefeatedScreen {
private:
    Texture bgTx;
    Sprite  bgSp;

    Font font;
    RectangleShape background;
    Text titleText;
    Text gemRewardText;

    RectangleShape continueBtn;
    Text continueBtnText;

    int choice;

public:
    BossDefeatedScreen();
    void setup();
    void setData(int gems);
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    int getChoice() { return choice; }
};