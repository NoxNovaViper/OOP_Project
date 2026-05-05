#include "characterChoiceUI.h"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

CharacterSelect::CharacterSelect() {

}

void CharacterSelect::set_up(int player_number) {
    choice = 0;
    selection_done = false;
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");

    bg_tx.loadFromFile("SnowBrosAssets/Start/UIbg3.png");
    bg_sp.setTexture(bg_tx);
    bg_sp.setScale(
        800.0f / bg_tx.getSize().x,
        600.0f / bg_tx.getSize().y);
    title_text.setFont(font);
    title_text.setString("Select Character");
    title_text.setCharacterSize(40);
    title_text.setFillColor(Color::White);
    title_text.setPosition(250, 30);

    // show which player is selectingB
    instruction_text.setFont(font);
    instruction_text.setString("Player " + to_string(player_number) +
        " - Choose your character");
    instruction_text.setCharacterSize(22);
    instruction_text.setFillColor(Color::Yellow);
    instruction_text.setPosition(220, 90);

    // character nick
    nick_btn.setSize(Vector2f(180, 200));
    nick_btn.setFillColor(Color(0, 150, 200));
    nick_btn.setPosition(80, 200);
    nick_text.setFont(font);
    nick_text.setString("Nick");
    nick_text.setCharacterSize(22);
    nick_text.setFillColor(Color::White);
    nick_text.setPosition(145, 175);
    nick_stats.setFont(font);
    nick_stats.setString("Speed: Normal\nRange: Medium");
    nick_stats.setCharacterSize(15);
    nick_stats.setFillColor(Color::White);
    nick_stats.setPosition(80, 410);


    nick_tex.loadFromFile("SnowBrosAssets/Start/nick.png");
    nick_sprite.setTexture(nick_tex);
    nick_sprite.setPosition(80, 200);
    nick_sprite.setScale(0.8f, 0.8f);

    // character tom
    tom_btn.setSize(Vector2f(180, 200));
    tom_btn.setFillColor(Color(0, 150, 200));
    tom_btn.setPosition(310, 200);
    tom_text.setFont(font);
    tom_text.setString("Tom");
    tom_text.setCharacterSize(22);
    tom_text.setFillColor(Color::White);
    tom_text.setPosition(380, 175);
    tom_stats.setFont(font);
    tom_stats.setString("Speed: Fast\nRange: Short");
    tom_stats.setCharacterSize(15);
    tom_stats.setFillColor(Color::White);
    tom_stats.setPosition(310, 410);


    tom_tex.loadFromFile("SnowBrosAssets/Start/tom.png");
    tom_sprite.setTexture(tom_tex);
    tom_sprite.setPosition(320, 206);
    tom_sprite.setScale(2.3f, 2.3f);

    // character tiger
    custom_btn.setSize(Vector2f(180, 200));
    custom_btn.setFillColor(Color(0, 150, 200));
    custom_btn.setPosition(540, 200);
    custom_text.setFont(font);
    custom_text.setString("tiger");
    custom_text.setCharacterSize(22);
    custom_text.setFillColor(Color::White);
    custom_text.setPosition(580, 175);
    custom_stats.setFont(font);
    custom_stats.setString("Speed: Slow\nRange: Long");
    custom_stats.setCharacterSize(15);
    custom_stats.setFillColor(Color::White);
    custom_stats.setPosition(540, 410);


    custom_tex.loadFromFile("SnowBrosAssets/Start/tiger.png");
    custom_sprite.setTexture(custom_tex);
    custom_sprite.setPosition(550, 206);
    custom_sprite.setScale(1.0f, 1.0f);
}

void CharacterSelect::handle_input(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse_pos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        if (nick_btn.getGlobalBounds().contains(mouse_pos))
        {
            choice = 1; selection_done = true;
        }
        else if (tom_btn.getGlobalBounds().contains(mouse_pos))
        {
            choice = 2; selection_done = true;
        }
        else if (custom_btn.getGlobalBounds().contains(mouse_pos))
        {
            choice = 3; selection_done = true;
        }
    }
}

void CharacterSelect::draw(RenderWindow& window) {
    window.draw(bg_sp);
    window.draw(title_text);
    window.draw(instruction_text);
    window.draw(nick_btn);
    window.draw(nick_sprite);
    window.draw(nick_text);
    window.draw(nick_stats);
    window.draw(tom_btn);
    window.draw(tom_sprite);
    window.draw(tom_text);
    window.draw(tom_stats);
    window.draw(custom_btn);
    window.draw(custom_sprite);
    window.draw(custom_text);
    window.draw(custom_stats);
}