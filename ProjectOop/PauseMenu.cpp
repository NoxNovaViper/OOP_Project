#include "PauseMenu.h"
PauseMenu::PauseMenu() {
    choice = 0;
    is_open = false;
}

void PauseMenu::set_up() {
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");

    bg_tx.loadFromFile("SnowBrosAssets/Start/menubg.png");
    bg_sp.setTexture(bg_tx);
    bg_sp.setScale(
        800.0f / bg_tx.getSize().x,
        600.0f / bg_tx.getSize().y);

    // title
    title_text.setFont(font);
    title_text.setString("Paused");
    title_text.setCharacterSize(36);
    title_text.setFillColor(Color::White);
    title_text.setPosition(340, 115);

    // resume
    resume_btn.setSize(Vector2f(250, 45));
    resume_btn.setFillColor(Color(0, 150, 200));
    resume_btn.setPosition(275, 175);
    resume_text.setFont(font);
    resume_text.setString("Resume");
    resume_text.setCharacterSize(22);
    resume_text.setFillColor(Color::White);
    resume_text.setPosition(355, 183);

    // shop
    shop_btn.setSize(Vector2f(250, 45));
    shop_btn.setFillColor(Color(0, 150, 200));
    shop_btn.setPosition(275, 235);
    shop_text.setFont(font);
    shop_text.setString("Open Shop");
    shop_text.setCharacterSize(22);
    shop_text.setFillColor(Color::White);
    shop_text.setPosition(330, 243);

    // save
    save_btn.setSize(Vector2f(250, 45));
    save_btn.setFillColor(Color(0, 150, 200));
    save_btn.setPosition(275, 295);
    save_text.setFont(font);
    save_text.setString("Save Game");
    save_text.setCharacterSize(22);
    save_text.setFillColor(Color::White);
    save_text.setPosition(330, 303);

    // logout
    logout_btn.setSize(Vector2f(250, 45));
    logout_btn.setFillColor(Color(0, 150, 200));
    logout_btn.setPosition(275, 355);
    logout_text.setFont(font);
    logout_text.setString("Logout");
    logout_text.setCharacterSize(22);
    logout_text.setFillColor(Color::White);
    logout_text.setPosition(360, 363);

    // exit
    exit_btn.setSize(Vector2f(250, 45));
    exit_btn.setFillColor(Color(0, 150, 200));
    exit_btn.setPosition(275, 415);
    exit_text.setFont(font);
    exit_text.setString("Exit to Menu");
    exit_text.setCharacterSize(22);
    exit_text.setFillColor(Color::White);
    exit_text.setPosition(315, 423);
}

void PauseMenu::handle_input(Event& event, RenderWindow& window) {
    if (!is_open) return;

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse_pos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        if (resume_btn.getGlobalBounds().contains(mouse_pos))
        {
            choice = 1; close();
        }
        else if (shop_btn.getGlobalBounds().contains(mouse_pos))
            choice = 2;
        else if (save_btn.getGlobalBounds().contains(mouse_pos))
            choice = 3;
        else if (logout_btn.getGlobalBounds().contains(mouse_pos))
            choice = 4;
        else if (exit_btn.getGlobalBounds().contains(mouse_pos))
            choice = 5;
    }
}

void PauseMenu::draw(RenderWindow& window) {
    if (!is_open) return;
    window.draw(bg_sp);
    window.draw(title_text);
    window.draw(resume_btn);
    window.draw(resume_text);
    window.draw(shop_btn);
    window.draw(shop_text);
    window.draw(save_btn);
    window.draw(save_text);
    window.draw(logout_btn);
    window.draw(logout_text);
    window.draw(exit_btn);
    window.draw(exit_text);
}