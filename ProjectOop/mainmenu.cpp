#include "mainmenu.h"
#include<iostream>
using namespace std;

Mainmenu::Mainmenu() {
    choice = 0;
    show_mode_select = false;
    mode_selected = false;
    is_single_player = true;
}

void Mainmenu::set_up() {
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");


    // background 
    if (!bg_tx.loadFromFile("SnowBrosAssets/Start/menubg.png")) {
        cout << "Background image not loaded!\n";
    }
    bg_sp.setTexture(bg_tx);
    bg_sp.setScale(
        800.0f / bg_tx.getSize().x,
        600.0f / bg_tx.getSize().y
    );

    //game title
    title_text.setFont(font);
    title_text.setString("Snow Bros");
    title_text.setCharacterSize(60);
    title_text.setFillColor(Color::White);
    title_text.setPosition(270, 60);

    //new_game_btn button
    new_game_btn.setSize(Vector2f(300, 55));
    new_game_btn.setFillColor(Color(0, 150, 200));
    new_game_btn.setPosition(250, 180);
    new_game_text.setFont(font);
    new_game_text.setString("New Game");
    new_game_text.setCharacterSize(24);
    new_game_text.setFillColor(Color::White);
    new_game_text.setPosition(320, 192);
    //continue_btn button
    continue_btn.setSize(Vector2f(300, 55));
    continue_btn.setFillColor(Color(0, 150, 200));
    continue_btn.setPosition(250, 260);
    continue_text.setFont(font);
    continue_text.setString("Continue");
    continue_text.setCharacterSize(24);
    continue_text.setFillColor(Color::White);
    continue_text.setPosition(330, 272);
    //leaderboard_btn button
    leaderboard_btn.setSize(Vector2f(300, 55));
    leaderboard_btn.setFillColor(Color(0, 150, 200));
    leaderboard_btn.setPosition(250, 340);
    leaderboard_text.setFont(font);
    leaderboard_text.setString("Leaderboard");
    leaderboard_text.setCharacterSize(24);
    leaderboard_text.setFillColor(Color::White);
    leaderboard_text.setPosition(300, 352);

    exit_btn.setSize(Vector2f(300, 55));
    exit_btn.setFillColor(Color(0, 150, 200));
    exit_btn.setPosition(250, 420);
    exit_text.setFont(font);
    exit_text.setString("Exit");
    exit_text.setCharacterSize(24);
    exit_text.setFillColor(Color::White);
    exit_text.setPosition(370, 432);

    // MULTILPLAYER OPTION

    mode_title.setFont(font);
    mode_title.setString("Select Mode");
    mode_title.setCharacterSize(40);
    mode_title.setFillColor(Color::White);
    mode_title.setPosition(290, 150);

    single_btn.setSize(Vector2f(300, 55));
    single_btn.setFillColor(Color(0, 180, 100));
    single_btn.setPosition(250, 280);
    single_text.setFont(font);
    single_text.setString("Single Player");
    single_text.setCharacterSize(24);
    single_text.setFillColor(Color::White);
    single_text.setPosition(290, 292);

    multi_btn.setSize(Vector2f(300, 55));
    multi_btn.setFillColor(Color(0, 180, 100));
    multi_btn.setPosition(250, 360);
    multi_text.setFont(font);
    multi_text.setString("Two Players");
    multi_text.setCharacterSize(24);
    multi_text.setFillColor(Color::White);
    multi_text.setPosition(310, 372);
}

void Mainmenu::handle_input(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse_pos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        if (!show_mode_select) {
            // mose clicks on screen logic
            if (new_game_btn.getGlobalBounds().contains(mouse_pos))
                show_mode_select = true;
            else if (continue_btn.getGlobalBounds().contains(mouse_pos))
                choice = 2;
            else if (leaderboard_btn.getGlobalBounds().contains(mouse_pos))
                choice = 3;
            else if (exit_btn.getGlobalBounds().contains(mouse_pos))
                choice = 4;
        }
        else {

            if (single_btn.getGlobalBounds().contains(mouse_pos)) {
                is_single_player = true;
                mode_selected = true;
                choice = 1;
            }
            else if (multi_btn.getGlobalBounds().contains(mouse_pos)) {
                is_single_player = false;
                mode_selected = true;
                choice = 1;
            }
        }
    }
}

void Mainmenu::draw(RenderWindow& window) {
    window.draw(bg_sp);
    window.draw(title_text);

    if (!show_mode_select) {
        // displaying main menu
        window.draw(new_game_btn);
        window.draw(new_game_text);
        window.draw(continue_btn);
        window.draw(continue_text);
        window.draw(leaderboard_btn);
        window.draw(leaderboard_text);
        window.draw(exit_btn);
        window.draw(exit_text);
    }
    else {
        // proceede selected mode 
        window.draw(mode_title);
        window.draw(single_btn);
        window.draw(single_text);
        window.draw(multi_btn);
        window.draw(multi_text);
    }
}