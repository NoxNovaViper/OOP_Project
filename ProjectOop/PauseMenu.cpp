#include "PauseMenu.h"
PauseMenu::PauseMenu() {
    choice = 0;
    isOpen = false;
}

void PauseMenu::setup() {
    font.loadFromFile("Starborn.ttf");

    bgTx.loadFromFile("BG.png");
    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y);

    // title
    titleText.setFont(font);
    titleText.setString("Paused");
    titleText.setCharacterSize(36);
    titleText.setFillColor(Color::White);
    titleText.setPosition(340, 115);

    // resume
    resumeBtn.setSize(Vector2f(250, 45));
    resumeBtn.setFillColor(Color(0, 150, 200));
    resumeBtn.setPosition(275, 175);
    resumeText.setFont(font);
    resumeText.setString("Resume");
    resumeText.setCharacterSize(22);
    resumeText.setFillColor(Color::White);
    resumeText.setPosition(355, 183);

    // shop
    shopBtn.setSize(Vector2f(250, 45));
    shopBtn.setFillColor(Color(0, 150, 200));
    shopBtn.setPosition(275, 235);
    shopText.setFont(font);
    shopText.setString("Open Shop");
    shopText.setCharacterSize(22);
    shopText.setFillColor(Color::White);
    shopText.setPosition(330, 243);

    // save
    saveBtn.setSize(Vector2f(250, 45));
    saveBtn.setFillColor(Color(0, 150, 200));
    saveBtn.setPosition(275, 295);
    saveText.setFont(font);
    saveText.setString("Save Game");
    saveText.setCharacterSize(22);
    saveText.setFillColor(Color::White);
    saveText.setPosition(330, 303);

    // logout
    logoutBtn.setSize(Vector2f(250, 45));
    logoutBtn.setFillColor(Color(0, 150, 200));
    logoutBtn.setPosition(275, 355);
    logoutText.setFont(font);
    logoutText.setString("Logout");
    logoutText.setCharacterSize(22);
    logoutText.setFillColor(Color::White);
    logoutText.setPosition(360, 363);

    // exit
    exitBtn.setSize(Vector2f(250, 45));
    exitBtn.setFillColor(Color(0, 150, 200));
    exitBtn.setPosition(275, 415);
    exitText.setFont(font);
    exitText.setString("Exit to Menu");
    exitText.setCharacterSize(22);
    exitText.setFillColor(Color::White);
    exitText.setPosition(315, 423);
}

void PauseMenu::handleInput(Event& event, RenderWindow& window) {
    if (!isOpen) return;

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        if (resumeBtn.getGlobalBounds().contains(mousePos))
        {
            choice = 1; close();
        }
        else if (shopBtn.getGlobalBounds().contains(mousePos))
            choice = 2;
        else if (saveBtn.getGlobalBounds().contains(mousePos))
            choice = 3;
        else if (logoutBtn.getGlobalBounds().contains(mousePos))
            choice = 4;
        else if (exitBtn.getGlobalBounds().contains(mousePos))
            choice = 5;
    }
}

void PauseMenu::draw(RenderWindow& window) {
    if (!isOpen) return;
    window.draw(bgSp);
    window.draw(titleText);
    window.draw(resumeBtn);
    window.draw(resumeText);
    window.draw(shopBtn);
    window.draw(shopText);
    window.draw(saveBtn);
    window.draw(saveText);
    window.draw(logoutBtn);
    window.draw(logoutText);
    window.draw(exitBtn);
    window.draw(exitText);
}