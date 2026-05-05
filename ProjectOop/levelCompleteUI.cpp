#include "LevelCompleteUI.h"
#include "AssetLoader.h"


LevelCompleteScreen::LevelCompleteScreen() {
    choice = 0;
}

void LevelCompleteScreen::set_up() {
    const Font& mainFont = Assets::font;

    bg_sp.setTexture(Assets::bg_t);
    bg_sp.setScale(
        800.0f / Assets::bg_t.getSize().x,
        600.0f / Assets::bg_t.getSize().y);


    title_text.setFont(mainFont);
    title_text.setString("Level Complete!");
    title_text.setCharacterSize(50);
    title_text.setFillColor(Color::Green);
    title_text.setPosition(210, 100);

    score_text.setFont(mainFont);
    score_text.setCharacterSize(28);
    score_text.setFillColor(Color::White);
    score_text.setPosition(280, 230);

    gems_text.setFont(mainFont);
    gems_text.setCharacterSize(28);
    gems_text.setFillColor(Color::White);
    gems_text.setPosition(280, 280);

    //button for next option
    next_btn.setSize(Vector2f(220, 55));
    next_btn.setFillColor(Color(0, 150, 200));
    next_btn.setPosition(290, 400);
    next_btn_text.setFont(mainFont);
    next_btn_text.setString("Next Level");
    next_btn_text.setCharacterSize(24);
    next_btn_text.setFillColor(Color::White);
    next_btn_text.setPosition(320, 413);
}

void LevelCompleteScreen::set_data(int score, int gems) {
    score_text.setString("Score: " + to_string(score));
    gems_text.setString("Gems:  " + to_string(gems));
}

void LevelCompleteScreen::handle_input(Event& event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse_pos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        if (next_btn.getGlobalBounds().contains(mouse_pos))
            choice = 1;
    }
}

void LevelCompleteScreen::draw(RenderWindow& window) {
    window.draw(bg_sp);
    window.draw(title_text);
    window.draw(score_text);
    window.draw(gems_text);
    window.draw(next_btn);
    window.draw(next_btn_text);
}