#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class CharacterSelect {
private:
    Font font;
    RectangleShape background;
    Text titleText;
    Text instructionText;
    Texture bgTx;
    Sprite  bgSp;

    // nick button
    RectangleShape nickBtn;
    Text nickText;
    Text nickStats;

    // tom button
    RectangleShape tomBtn;
    Text tomText;
    Text tomStats;

    // custom button
    RectangleShape customBtn;
    Text customText;
    Text customStats;

    // images
    Texture nickTex;
    Texture tomTex;
    Texture customTex;
    Sprite nickSprite;
    Sprite tomSprite;
    Sprite customSprite;

    int choice;
    bool selectionDone;

public:
    CharacterSelect();
    void setup(int playerNumber);  
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    bool getSelectionDone() { return selectionDone; }
    int getChoice() { return choice; }
};