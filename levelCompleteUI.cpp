#include "LevelCompleteUI.h"


LevelCompleteScreen::LevelCompleteScreen() {
    choice = 0;
}

void LevelCompleteScreen::setup() {
    font.loadFromFile("arial.ttf");

    bgTx.loadFromFile("BG.png");
    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y);


    titleText.setFont(font);
    titleText.setString("Level Complete!");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::Green);
    titleText.setPosition(210, 100);

    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(280, 230);

    gemsText.setFont(font);
    gemsText.setCharacterSize(28);
    gemsText.setFillColor(Color::White);
    gemsText.setPosition(280, 280);

    //button for next option
    nextBtn.setSize(Vector2f(220, 55));
    nextBtn.setFillColor(Color(0, 150, 200));
    nextBtn.setPosition(290, 400);
    nextBtnText.setFont(font);
    nextBtnText.setString("Next Level");
    nextBtnText.setCharacterSize(24);
    nextBtnText.setFillColor(Color::White);
    nextBtnText.setPosition(320, 413);
}

void LevelCompleteScreen::setData(int score, int gems) {
    scoreText.setString("Score: " + to_string(score));
    gemsText.setString("Gems:  " + to_string(gems));
}

void LevelCompleteScreen::handleInput(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        if (nextBtn.getGlobalBounds().contains(mousePos))
            choice = 1;
    }
}

void LevelCompleteScreen::draw(RenderWindow& window) {
    window.draw(bgSp);
    window.draw(titleText);
    window.draw(scoreText);
    window.draw(gemsText);
    window.draw(nextBtn);
    window.draw(nextBtnText);
}