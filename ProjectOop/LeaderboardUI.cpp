#include "LeaderboardUI.h"
#include <iostream>
using namespace std;
using namespace sf;

LeaderboardUI::LeaderboardUI() : is_open(false), count(0) {}

void LeaderboardUI::set_up() {
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");
    
    if (!bg_tx.loadFromFile("SnowBrosAssets/Start/menubg.png")) {
        cout << "Leaderboard BG not loaded\n";
    }
    bg_sp.setTexture(bg_tx);
    bg_sp.setScale(800.0f / bg_tx.getSize().x, 600.0f / bg_tx.getSize().y);

    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(50);
    title.setFillColor(Color::Yellow);
    title.setPosition(220, 50);

    column_headers.setFont(font);
    column_headers.setString("RANK   NAME           SCORE   LEVEL");
    column_headers.setCharacterSize(20);
    column_headers.setFillColor(Color::Cyan);
    column_headers.setPosition(150, 130);

    for (int i = 0; i < 10; i++) {
        entries[i].setFont(font);
        entries[i].setCharacterSize(18);
        entries[i].setFillColor(Color::White);
        entries[i].setPosition(150, 170 + i * 35);
    }

    back_btn.setSize(Vector2f(200, 50));
    back_btn.setFillColor(Color(200, 50, 50));
    back_btn.setPosition(300, 530);

    back_text.setFont(font);
    back_text.setString("BACK");
    back_text.setCharacterSize(20);
    back_text.setFillColor(Color::White);
    back_text.setPosition(365, 542);
}

void LeaderboardUI::load_data(Database& database) {
    database.load_leaderboard(usernames, scores, levels, count);
    for (int i = 0; i < 10; i++) {
        if (i < count) {
            string rank_str = to_string(i + 1);
            if (i < 9) rank_str = " " + rank_str; // padding
            
            string name_str = usernames[i];
            while (name_str.length() < 15) name_str += " "; // padding
            
            string score_str = to_string(scores[i]);
            while (score_str.length() < 8) score_str = " " + score_str;
            
            string level_str = to_string(levels[i]);

            entries[i].setString(rank_str + "      " + name_str + " " + score_str + "      " + level_str);
        } else {
            entries[i].setString("");
        }
    }
}

void LeaderboardUI::handle_input(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse_pos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
        if (back_btn.getGlobalBounds().contains(mouse_pos)) {
            is_open = false;
        }
    }
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        is_open = false;
    }
}

void LeaderboardUI::draw(RenderWindow& window) {
    window.draw(bg_sp);
    window.draw(title);
    window.draw(column_headers);
    for (int i = 0; i < 10; i++) {
        window.draw(entries[i]);
    }
    window.draw(back_btn);
    window.draw(back_text);
}
