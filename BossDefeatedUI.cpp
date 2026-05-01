#include "BossDefeatedUI.h"

BossDefeatedScreen::BossDefeatedScreen() {
    choice = 0;
}

void BossDefeatedScreen::setup() {
    font.loadFromFile("arial.ttf");

    bgTx.loadFromFile("UIbg3.png");
    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y);

    titleText.setFont(font);
    titleText.setString("Boss Defeated!");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::White);
    titleText.setPosition(220, 150);

    gemRewardText.setFont(font);
    gemRewardText.setCharacterSize(30);
    gemRewardText.setFillColor(Color::White);
    gemRewardText.setPosition(270, 280);

    continueBtn.setSize(Vector2f(220, 55));
    continueBtn.setFillColor(Color(0, 150, 200));
    continueBtn.setPosition(290, 400);
    continueBtnText.setFont(font);
    continueBtnText.setString("Continue");
    continueBtnText.setCharacterSize(24);
    continueBtnText.setFillColor(Color::White);
    continueBtnText.setPosition(340, 413);
}

void BossDefeatedScreen::setData(int gems) {
    gemRewardText.setString("Gems Earned: " + to_string(gems));
}

void BossDefeatedScreen::handleInput(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {

        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        if (continueBtn.getGlobalBounds().contains(mousePos))
            choice = 1;
    }
}

void BossDefeatedScreen::draw(RenderWindow& window) {
    window.draw(bgSp);
    window.draw(titleText);
    window.draw(gemRewardText);
    window.draw(continueBtn);
    window.draw(continueBtnText);
}