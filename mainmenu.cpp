#include "Mainmenu.h"
#include<iostream>
using namespace std;

Mainmenu::Mainmenu() {
    choice = 0;
    showModeSelect = false;
    modeSelected = false;
    isSinglePlayer = true;
}

void Mainmenu::setup() {
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");

    
    // background 
    if (!bgTx.loadFromFile("SnowBrosAssets/Start/menubg.png")) {
        cout << "Background image not loaded!\n";
    }
    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y
    );

                //game title
    titleText.setFont(font);
    titleText.setString("Snow Bros");
    titleText.setCharacterSize(60);
    titleText.setFillColor(Color::White);
    titleText.setPosition(270, 60);

                //newGame button
    newGameBtn.setSize(Vector2f(300, 55));
    newGameBtn.setFillColor(Color(0, 150, 200));
    newGameBtn.setPosition(250, 180);
    newGameText.setFont(font);
    newGameText.setString("New Game");
    newGameText.setCharacterSize(24);
    newGameText.setFillColor(Color::White);
    newGameText.setPosition(320, 192);
                            //contiune button
    continueBtn.setSize(Vector2f(300, 55));
    continueBtn.setFillColor(Color(0, 150, 200));
    continueBtn.setPosition(250, 260);
    continueText.setFont(font);
    continueText.setString("Continue");
    continueText.setCharacterSize(24);
    continueText.setFillColor(Color::White);
    continueText.setPosition(330, 272);
                    //leaderboard button
    leaderboardBtn.setSize(Vector2f(300, 55));
    leaderboardBtn.setFillColor(Color(0, 150, 200));
    leaderboardBtn.setPosition(250, 340);
    leaderboardText.setFont(font);
    leaderboardText.setString("Leaderboard");
    leaderboardText.setCharacterSize(24);
    leaderboardText.setFillColor(Color::White);
    leaderboardText.setPosition(300, 352);

    exitBtn.setSize(Vector2f(300, 55));
    exitBtn.setFillColor(Color(0, 150, 200));
    exitBtn.setPosition(250, 420);
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(Color::White);
    exitText.setPosition(370, 432);

    // MUTILPLAYER OPTION

    modeTitle.setFont(font);
    modeTitle.setString("Select Mode");
    modeTitle.setCharacterSize(40);
    modeTitle.setFillColor(Color::White);
    modeTitle.setPosition(290, 150);

    singleBtn.setSize(Vector2f(300, 55));
    singleBtn.setFillColor(Color(0, 180, 100));
    singleBtn.setPosition(250, 280);
    singleText.setFont(font);
    singleText.setString("Single Player");
    singleText.setCharacterSize(24);
    singleText.setFillColor(Color::White);
    singleText.setPosition(290, 292);

    multiBtn.setSize(Vector2f(300, 55));
    multiBtn.setFillColor(Color(0, 180, 100));
    multiBtn.setPosition(250, 360);
    multiText.setFont(font);
    multiText.setString("Two Players");
    multiText.setCharacterSize(24);
    multiText.setFillColor(Color::White);
    multiText.setPosition(310, 372);
}

void Mainmenu::handleInput(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        if (!showModeSelect) {
            // mose clicks on screen logic
            if (newGameBtn.getGlobalBounds().contains(mousePos))
                showModeSelect = true;
            else if (continueBtn.getGlobalBounds().contains(mousePos))
                choice = 2;
            else if (leaderboardBtn.getGlobalBounds().contains(mousePos))
                choice = 3;
            else if (exitBtn.getGlobalBounds().contains(mousePos))
                choice = 4;
        }
        else {
            
            if (singleBtn.getGlobalBounds().contains(mousePos)) {
                isSinglePlayer = true;
                modeSelected = true;
                choice = 1;
            }
            else if (multiBtn.getGlobalBounds().contains(mousePos)) {
                isSinglePlayer = false;
                modeSelected = true;
                choice = 1;
            }
        }
    }
}

void Mainmenu::draw(RenderWindow& window) {
    window.draw(bgSp);
    window.draw(titleText);

    if (!showModeSelect) {
        // displaying main menu
        window.draw(newGameBtn);
        window.draw(newGameText);
        window.draw(continueBtn);
        window.draw(continueText);
        window.draw(leaderboardBtn);
        window.draw(leaderboardText);
        window.draw(exitBtn);
        window.draw(exitText);
    }
    else {
        // proceede selected mode 
        window.draw(modeTitle);
        window.draw(singleBtn);
        window.draw(singleText);
        window.draw(multiBtn);
        window.draw(multiText);
    }
}
