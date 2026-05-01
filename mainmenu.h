#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Mainmenu {
private:
    int choice;
    Texture bgTx;
    Sprite bgSp;
    Font font;
    RectangleShape background;
    Text titleText;

    // main buttons
    RectangleShape newGameBtn;
    Text newGameText;
    RectangleShape continueBtn;
    Text continueText;
    RectangleShape leaderboardBtn;
    Text leaderboardText;
    RectangleShape exitBtn;
    Text exitText;

    // mode select buttons — added
    bool showModeSelect;
    bool modeSelected;
    bool isSinglePlayer;
    Text modeTitle;
    RectangleShape singleBtn;
    Text singleText;
    RectangleShape multiBtn;
    Text multiText;

public:
    Mainmenu();
    void setup();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    int getChoice() { return choice; }
    bool getModeSelected() { return modeSelected; }
    bool getIsSinglePlayer() { return isSinglePlayer; }
};