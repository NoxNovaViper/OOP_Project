#include "shop.h"

Shop::Shop() {
    isopen = false;
    showMessage = false;
}

void Shop::setup() {
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");

    bgTx.loadFromFile("SnowBrosAssets/Start/menubg.png");
    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y);

    // title
    titleText.setFont(font);
    titleText.setString("Shop");
    titleText.setCharacterSize(36);
    titleText.setFillColor(Color::Yellow);
    titleText.setPosition(370, 60);

    // gems display
    gemsText.setFont(font);
    gemsText.setCharacterSize(22);
    gemsText.setFillColor(Color::Yellow);
    gemsText.setPosition(160, 105);

    // message
    messageText.setFont(font);
    messageText.setCharacterSize(18);
    messageText.setPosition(160, 530);

    // extra life - 50 gems
    extraLifeBtn.setSize(Vector2f(440, 50));
    extraLifeBtn.setFillColor(Color(0, 150, 200));
    extraLifeBtn.setPosition(160, 140);
    extraLifeText.setFont(font);
    extraLifeText.setString("Extra Life          - 50 gems");
    extraLifeText.setCharacterSize(20);
    extraLifeText.setFillColor(Color::White);
    extraLifeText.setPosition(170, 152);

    // speed boost - 20 gems
    speedBtn.setSize(Vector2f(440, 50));
    speedBtn.setFillColor(Color(0, 150, 200));
    speedBtn.setPosition(160, 205);
    speedText.setFont(font);
    speedText.setString("Speed Boost (30s)   - 20 gems");
    speedText.setCharacterSize(20);
    speedText.setFillColor(Color::White);
    speedText.setPosition(170, 217);

    // snowball power - 30 gems
    snowballBtn.setSize(Vector2f(440, 50));
    snowballBtn.setFillColor(Color(0, 150, 200));
    snowballBtn.setPosition(160, 270);
    snowballText.setFont(font);
    snowballText.setString("Snowball Power      - 30 gems");
    snowballText.setCharacterSize(20);
    snowballText.setFillColor(Color::White);
    snowballText.setPosition(170, 282);

    // distance increase - 25 gems
    distanceBtn.setSize(Vector2f(440, 50));
    distanceBtn.setFillColor(Color(0, 150, 200));
    distanceBtn.setPosition(160, 335);
    distanceText.setFont(font);
    distanceText.setString("Distance Increase   - 25 gems");
    distanceText.setCharacterSize(20);
    distanceText.setFillColor(Color::White);
    distanceText.setPosition(170, 347);

    // balloon mode - 35 gems
    balloonBtn.setSize(Vector2f(440, 50));
    balloonBtn.setFillColor(Color(0, 150, 200));
    balloonBtn.setPosition(160, 400);
    balloonText.setFont(font);
    balloonText.setString("Balloon Mode (30s)  - 35 gems");
    balloonText.setCharacterSize(20);
    balloonText.setFillColor(Color::White);
    balloonText.setPosition(170, 412);

    // close button
    closeBtn.setSize(Vector2f(200, 45));
    closeBtn.setFillColor(Color(200, 50, 50));
    closeBtn.setPosition(300, 465);
    closeBtnText.setFont(font);
    closeBtnText.setString("Close Shop");
    closeBtnText.setCharacterSize(22);
    closeBtnText.setFillColor(Color::White);
    closeBtnText.setPosition(325, 474);
}

void Shop::opentheShop() {
    isopen = true;
}

void Shop::ExtraLife(Player& player) {
    if (player.spendgems(50))
        player.addLives();
}

void Shop::SpeedBoost(Player& player) {
    if (player.spendgems(20))
        player.activateSpeedboost();
}

void Shop::SnowballPower(Player& player) {
    if (player.spendgems(30))
        player.activateSnowballpower();
}

void Shop::DistanceIncrease(Player& player) {
    if (player.spendgems(25))
        player.activateDistanceincreased();
}

void Shop::BalloonMode(Player& player) {
    if (player.spendgems(35))
        player.activateBalloonmode();
}

void Shop::handleInput(Event& event, RenderWindow& window, Player& player) {
    if (!isopen) return;

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        if (extraLifeBtn.getGlobalBounds().contains(mousePos)) {
            if (player.spendgems(50)) {
                player.addLives();
                showMessage = true;
                messageText.setFillColor(Color::Green);
                messageText.setString("Extra life purchased!");
            }
            else {
                showMessage = true;
                messageText.setFillColor(Color::Red);
                messageText.setString("Not enough gems!");
            }
        }
        else if (speedBtn.getGlobalBounds().contains(mousePos)) {
            if (player.spendgems(20)) {
                player.activateSpeedboost();
                showMessage = true;
                messageText.setFillColor(Color::Green);
                messageText.setString("Speed boost activated!");
            }
            else {
                showMessage = true;
                messageText.setFillColor(Color::Red);
                messageText.setString("Not enough gems!");
            }
        }
        else if (snowballBtn.getGlobalBounds().contains(mousePos)) {
            if (player.spendgems(30)) {
                player.activateSnowballpower();
                showMessage = true;
                messageText.setFillColor(Color::Green);
                messageText.setString("Snowball power activated!");
            }
            else {
                showMessage = true;
                messageText.setFillColor(Color::Red);
                messageText.setString("Not enough gems!");
            }
        }
        else if (distanceBtn.getGlobalBounds().contains(mousePos)) {
            if (player.spendgems(25)) {
                player.activateDistanceincreased();
                showMessage = true;
                messageText.setFillColor(Color::Green);
                messageText.setString("Distance increased!");
            }
            else {
                showMessage = true;
                messageText.setFillColor(Color::Red);
                messageText.setString("Not enough gems!");
            }
        }
        else if (balloonBtn.getGlobalBounds().contains(mousePos)) {
            if (player.spendgems(35)) {
                player.activateBalloonmode();
                showMessage = true;
                messageText.setFillColor(Color::Green);
                messageText.setString("Balloon mode activated!");
            }
            else {
                showMessage = true;
                messageText.setFillColor(Color::Red);
                messageText.setString("Not enough gems!");
            }
        }
        else if (closeBtn.getGlobalBounds().contains(mousePos)) {
            close();
            showMessage = false;
        }
    }
}

void Shop::draw(RenderWindow& window, Player& player) {
    if (!isopen) return;

    // update gems every frame
    gemsText.setString("Your Gems: " + to_string(player.getGemCount()));

    window.draw(bgSp);
    window.draw(titleText);
    window.draw(gemsText);
    window.draw(extraLifeBtn);
    window.draw(extraLifeText);
    window.draw(speedBtn);
    window.draw(speedText);
    window.draw(snowballBtn);
    window.draw(snowballText);
    window.draw(distanceBtn);
    window.draw(distanceText);
    window.draw(balloonBtn);
    window.draw(balloonText);
    window.draw(closeBtn);
    window.draw(closeBtnText);

    if (showMessage)
        window.draw(messageText);
}