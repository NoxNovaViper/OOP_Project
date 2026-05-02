#include "LevelCompleteUI.h"
#include "AssetLoader.h"


LevelCompleteScreen::LevelCompleteScreen() {
    choice = 0;
}

void LevelCompleteScreen::setup() {
    const Font& mainFont = Assets::font;

    bgSp.setTexture(Assets::bg_t);
    bgSp.setScale(
        800.0f / Assets::bg_t.getSize().x,
        600.0f / Assets::bg_t.getSize().y);


    titleText.setFont(mainFont);
    titleText.setString("Level Complete!");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::Green);
    titleText.setPosition(210, 100);

    scoreText.setFont(mainFont);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(280, 230);

    gemsText.setFont(mainFont);
    gemsText.setCharacterSize(28);
    gemsText.setFillColor(Color::White);
    gemsText.setPosition(280, 280);

    //button for next option
    nextBtn.setSize(Vector2f(220, 55));
    nextBtn.setFillColor(Color(0, 150, 200));
    nextBtn.setPosition(290, 400);
    nextBtnText.setFont(mainFont);
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