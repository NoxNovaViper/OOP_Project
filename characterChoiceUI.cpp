#include "characterChoiceUI.h"
#include<iostream>
using namespace sf;

CharacterSelect::CharacterSelect() {
    choice = 0;
    selectionDone = false;
}

void CharacterSelect::setup(int playerNumber) {
    font.loadFromFile("arial.ttf");

    bgTx.loadFromFile("UIbg3.png");
    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y);
    titleText.setFont(font);
    titleText.setString("Select Character");
    titleText.setCharacterSize(40);
    titleText.setFillColor(Color::White);
    titleText.setPosition(250, 30);

    // show which player is selecting
    instructionText.setFont(font);
    instructionText.setString("Player " + std::to_string(playerNumber) +
        " - Choose your character");
    instructionText.setCharacterSize(22);
    instructionText.setFillColor(Color::Yellow);
    instructionText.setPosition(220, 90);

    // character nick
    nickBtn.setSize(Vector2f(180, 200));
    nickBtn.setFillColor(Color(0, 150, 200));
    nickBtn.setPosition(80, 200);
    nickText.setFont(font);
    nickText.setString("Nick");
    nickText.setCharacterSize(22);
    nickText.setFillColor(Color::White);
    nickText.setPosition(145, 175);
    nickStats.setFont(font);
    nickStats.setString("Speed: Normal\nRange: Medium");
    nickStats.setCharacterSize(15);
    nickStats.setFillColor(Color::White);
    nickStats.setPosition(80, 410);


    nickTex.loadFromFile("nick.png");
    nickSprite.setTexture(nickTex);
    nickSprite.setPosition(80, 200);
    nickSprite.setScale(0.8f, 0.8f);

    // character tom
    tomBtn.setSize(Vector2f(180, 200));
    tomBtn.setFillColor(Color(0, 150, 200));
    tomBtn.setPosition(310, 200);
    tomText.setFont(font);
    tomText.setString("Tom");
    tomText.setCharacterSize(22);
    tomText.setFillColor(Color::White);
    tomText.setPosition(380, 175);
    tomStats.setFont(font);
    tomStats.setString("Speed: Fast\nRange: Short");
    tomStats.setCharacterSize(15);
    tomStats.setFillColor(Color::White);
    tomStats.setPosition(310, 410);

    
    tomTex.loadFromFile("tom.png");
    tomSprite.setTexture(tomTex);
    tomSprite.setPosition(320, 206);
    tomSprite.setScale(2.3f, 2.3f);

    // character tiger
    customBtn.setSize(Vector2f(180, 200));
    customBtn.setFillColor(Color(0, 150, 200));
    customBtn.setPosition(540, 200);
    customText.setFont(font);
    customText.setString("tiger");
    customText.setCharacterSize(22);
    customText.setFillColor(Color::White);
    customText.setPosition(580, 175);
    customStats.setFont(font);
    customStats.setString("Speed: Slow\nRange: Long");
    customStats.setCharacterSize(15);
    customStats.setFillColor(Color::White);
    customStats.setPosition(540, 410);

    
    customTex.loadFromFile("tiger.png");
    customSprite.setTexture(customTex);
    customSprite.setPosition(550, 206);
    customSprite.setScale(1.0f, 1.0f);
}

void CharacterSelect::handleInput(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        if (nickBtn.getGlobalBounds().contains(mousePos))
        {
            choice = 1; selectionDone = true;
        }
        else if (tomBtn.getGlobalBounds().contains(mousePos))
        {
            choice = 2; selectionDone = true;
        }
        else if (customBtn.getGlobalBounds().contains(mousePos))
        {
            choice = 3; selectionDone = true;
        }
    }
}

void CharacterSelect::draw(RenderWindow& window) {
    window.draw(bgSp);
    window.draw(titleText);
    window.draw(instructionText);
    window.draw(nickBtn);
    window.draw(nickSprite);
    window.draw(nickText);
    window.draw(nickStats);
    window.draw(tomBtn);
    window.draw(tomSprite);
    window.draw(tomText);
    window.draw(tomStats);
    window.draw(customBtn);
    window.draw(customSprite);
    window.draw(customText);
    window.draw(customStats);
}