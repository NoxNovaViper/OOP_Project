#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class LoginScreen {
private:
    sf::Font font;
    sf::Text username;
    sf::Text prompt;
public:
    LoginScreen() {
        if (!font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf")) {
            std::cout << "Rip - Font not found" << std::endl;
        }
        username.setFont(font);
        username.setFillColor(sf::Color::White);
        username.setCharacterSize(24);
        username.setPosition(300, 300);
        username.setString("");

        prompt.setFont(font);
        prompt.setFillColor(sf::Color::Yellow);
        prompt.setCharacterSize(30);
        prompt.setPosition(250, 200);
        prompt.setString("Enter Username:");
    }

    void handleInput(sf::Event& event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) { // Backspace
                std::string str = username.getString();
                if (!str.empty()) {
                    str.pop_back();
                    username.setString(str);
                }
            } else if (event.text.unicode < 128) {
                username.setString(username.getString() + sf::String(event.text.unicode));
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(prompt);
        window.draw(username);
    }

    std::string getUsername() {
        return username.getString();
    }

    std::string select_skin(int i) {
        switch (i) {
            case 1: return "SnowBrosAssets/Images/Nick.png";
            case 2: return "SnowBrosAssets/Images/Tom.png";
            case 3: return "SnowBrosAssets/Images/Bob.png";
            default: return "SnowBrosAssets/Images/Nick.png";
        }
    }
};
