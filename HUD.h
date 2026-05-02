#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class HUD {
private:
    Font font;

    // player 1
    Text p1ScoreText;
    Text p1LivesText;
    Text p1GemsText;

    // player 2
    Text p2ScoreText;
    Text p2LivesText;
    Text p2GemsText;

    // level
    Text levelText;

    // powerup
    Text powerupText;

    // boss health
    RectangleShape bossHealthBg;
    RectangleShape bossHealthBar;
    Text bossHealthText;

    bool isBossLevel;
    bool isSinglePlayer;

public:
    HUD(bool singlePlayer);
    void setup();
    void update(int p1Score, int p1Lives, int p1Gems,
        int p2Score, int p2Lives, int p2Gems,
        int level, int totalLevels,
        string powerup,
        int bossHealth, int bossMaxHealth);
    void setBossLevel(bool value);
    void draw(RenderWindow& window);
};