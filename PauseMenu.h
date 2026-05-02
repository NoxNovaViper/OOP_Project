#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class PauseMenu {
private:
    Texture bgTx;
    Sprite  bgSp;

    Font font;
    RectangleShape background;
    Text titleText;

    RectangleShape resumeBtn;
    Text resumeText;

    RectangleShape shopBtn;
    Text shopText;

    RectangleShape saveBtn;
    Text saveText;

    RectangleShape logoutBtn;
    Text logoutText;

    RectangleShape exitBtn;
    Text exitText;

    int choice;
    bool isOpen;

public:
    PauseMenu();
    void setup();
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);

    void open() { isOpen = true; }
    void close() { isOpen = false; }
    bool getIsOpen() { return isOpen; }
    int getChoice() { return choice; }
    void resetChoice() { choice = 0; }
};