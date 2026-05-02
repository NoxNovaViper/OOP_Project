#include "GameOverUI.h"
#include "AssetLoader.h"

GameOverScreen::GameOverScreen() {
    choice = 0;
}

void GameOverScreen::setup() {
    const Font& mainFont = font;
    bgSp.setTexture(Assets::start_t1); // Using start screen as placeholder bg
    bgSp.setScale(
        800.0f / Assets::start_t1.getSize().x,
        600.0f / Assets::start_t1.getSize().y);
    titleText.setFont(mainFont);
    titleText.setString("Game Over");
    titleText.setCharacterSize(55);
    titleText.setFillColor(Color::White);
    titleText.setPosition(270, 100);

    scoreText.setFont(mainFont);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(280, 220);

    levelText.setFont(mainFont);
    levelText.setCharacterSize(28);
    levelText.setFillColor(Color::White);
    levelText.setPosition(280, 270);

    retryBtn.setSize(Vector2f(200, 50));
    retryBtn.setFillColor(Color(0, 150, 200));
    retryBtn.setPosition(180, 380);
    retryBtnText.setFont(font);
    retryBtnText.setString("Retry");
    retryBtnText.setCharacterSize(24);
    retryBtnText.setFillColor(Color::White);
    retryBtnText.setPosition(250, 390);

    menuBtn.setSize(Vector2f(200, 50));
    menuBtn.setFillColor(Color(0, 150, 200));
    menuBtn.setPosition(420, 380);
    menuBtnText.setFont(font);
    menuBtnText.setString("Main Menu");
    menuBtnText.setCharacterSize(24);
    menuBtnText.setFillColor(Color::White);
    menuBtnText.setPosition(445, 390);
}

void GameOverScreen::setData(int score, int level) {
    scoreText.setString("Final Score: " + to_string(score));
    levelText.setString("Level Reached: " + to_string(level));
}

void GameOverScreen::handleInput(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        if (retryBtn.getGlobalBounds().contains(mousePos))
            choice = 1;
        else if (menuBtn.getGlobalBounds().contains(mousePos))
            choice = 2;
    }
}

void GameOverScreen::draw(RenderWindow& window) {
    window.draw(bgSp);
    window.draw(titleText);
    window.draw(scoreText);
    window.draw(levelText);
    window.draw(retryBtn);
    window.draw(retryBtnText);
    window.draw(menuBtn);
    window.draw(menuBtnText);
}