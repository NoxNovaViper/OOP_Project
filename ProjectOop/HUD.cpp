#include "HUD.h"
#include "AssetLoader.h"

HUD::HUD(bool singlePlayer) {
    isSinglePlayer = singlePlayer;
    isBossLevel = false;
}

void HUD::setup() {
    // Use the centralized font from Assets
    const Font& mainFont = Assets::font;
    
    // player 1 on top left
    p1ScoreText.setFont(mainFont);
    p1ScoreText.setCharacterSize(20);
    p1ScoreText.setFillColor(Color::White);
    p1ScoreText.setPosition(10, 10);

    p1LivesText.setFont(font);
    p1LivesText.setCharacterSize(20);
    p1LivesText.setFillColor(Color::White);
    p1LivesText.setPosition(10, 35);

    p1GemsText.setFont(font);
    p1GemsText.setCharacterSize(20);
    p1GemsText.setFillColor(Color::Yellow);
    p1GemsText.setPosition(10, 60);

    // player 2 on  top right
    p2ScoreText.setFont(font);
    p2ScoreText.setCharacterSize(20);
    p2ScoreText.setFillColor(Color::White);
    p2ScoreText.setPosition(600, 10);

    p2LivesText.setFont(font);
    p2LivesText.setCharacterSize(20);
    p2LivesText.setFillColor(Color::White);
    p2LivesText.setPosition(600, 35);

    p2GemsText.setFont(font);
    p2GemsText.setCharacterSize(20);
    p2GemsText.setFillColor(Color::Yellow);
    p2GemsText.setPosition(600, 60);

    // level at top center
    levelText.setFont(font);
    levelText.setCharacterSize(22);
    levelText.setFillColor(Color::White);
    levelText.setPosition(340, 10);

    // powerup bottom
    powerupText.setFont(font);
    powerupText.setCharacterSize(18);
    powerupText.setFillColor(Color::Cyan);
    powerupText.setPosition(10, 560);

    // boss health bar background
    bossHealthBg.setSize(Vector2f(400, 25));
    bossHealthBg.setFillColor(Color(100, 0, 0));
    bossHealthBg.setPosition(200, 40);

    // boss health bar fill
    bossHealthBar.setSize(Vector2f(400, 25));
    bossHealthBar.setFillColor(Color::Red);
    bossHealthBar.setPosition(200, 40);

    // boss text
    bossHealthText.setFont(font);
    bossHealthText.setCharacterSize(16);
    bossHealthText.setFillColor(Color::White);
    bossHealthText.setPosition(370, 44);
    bossHealthText.setString("BOSS");
}

void HUD::update(int p1Score, int p1Lives, int p1Gems, int p2Score, int p2Lives, int p2Gems, int level, int totalLevels,
    string powerup,
    int bossHealth, int bossMaxHealth) {

    // update player 1
    p1ScoreText.setString("P1 Score: " + to_string(p1Score));
    p1LivesText.setString("P1 Lives: " + to_string(p1Lives));
    p1GemsText.setString("P1 Gems:  " + to_string(p1Gems));

    // update player 2 only in multiplayer
    if (!isSinglePlayer) {
        p2ScoreText.setString("P2 Score: " + to_string(p2Score));
        p2LivesText.setString("P2 Lives: " + to_string(p2Lives));
        p2GemsText.setString("P2 Gems:  " + to_string(p2Gems));
    }

    // update level
    levelText.setString("Level: " + to_string(level) +
        "/" + to_string(totalLevels));

    // update powerup
    if (powerup == "")
        powerupText.setString("No PowerUp Active");
    else
        powerupText.setString("PowerUp: " + powerup);

    // shrink boss bar as health goes down
    if (isBossLevel && bossMaxHealth > 0) {
        float ratio = (float)bossHealth / (float)bossMaxHealth;
        bossHealthBar.setSize(Vector2f(400 * ratio, 25));
    }
}

void HUD::setBossLevel(bool value) {
    isBossLevel = value;
}

void HUD::draw(RenderWindow& window) {
    window.draw(p1ScoreText);
    window.draw(p1LivesText);
    window.draw(p1GemsText);

    // draw p2 if multiplayer
    if (!isSinglePlayer) {
        window.draw(p2ScoreText);
        window.draw(p2LivesText);
        window.draw(p2GemsText);
    }

    window.draw(levelText);
    window.draw(powerupText);

    //  draw boss bar if  boss levels
    if (isBossLevel) {
        window.draw(bossHealthBg);
        window.draw(bossHealthBar);
        window.draw(bossHealthText);
    }
}