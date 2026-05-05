#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;
using namespace std;

class Shop {
private:
    bool isopen;
    Texture bgTx;
    Sprite  bgSp;
    Font font;
    RectangleShape background;
    Text titleText;
    Text gemsText;
    Text messageText;
    bool showMessage;

    RectangleShape extraLifeBtn;
    Text extraLifeText;

    RectangleShape speedBtn;
    Text speedText;

    RectangleShape snowballBtn;
    Text snowballText;

    RectangleShape distanceBtn;
    Text distanceText;

    RectangleShape balloonBtn;
    Text balloonText;

    RectangleShape closeBtn;
    Text closeBtnText;

public:
    Shop();
    void setup();
    void opentheShop();
    void ExtraLife(Player& player);
    void SpeedBoost(Player& player);
    void SnowballPower(Player& player);
    void DistanceIncrease(Player& player);
    void BalloonMode(Player& player);
    void handleInput(Event& event, RenderWindow& window, Player& player);
    void draw(RenderWindow& window, Player& player);
    void close() { isopen = false; }
    bool getIsOpen() const { return isopen; }
};