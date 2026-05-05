#include "LoginScreen.h"

using namespace sf;
LoginScreen::LoginScreen() {
    is_logged_in = false;
    active_box = 1; // cursor on username 

    show_error = false;
    username_str = "";
    password_str = "";
    error_message = "";
}

void LoginScreen::set_up() {

    //loading font
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");
    //background 
    bg_tx.loadFromFile("SnowBrosAssets/Start/BG.png");

    bg_sp.setTexture(bg_tx);
    bg_sp.setScale(
        800.0f / bg_tx.getSize().x,
        600.0f / bg_tx.getSize().y
    );

    title_text.setFont(font);
    title_text.setString("Snow Bros");
    title_text.setCharacterSize(50);
    title_text.setFillColor(Color::White);
    title_text.setPosition(300, 60);

    // username title
    username_label.setFont(font);
    username_label.setString("Username:");
    username_label.setCharacterSize(22);
    username_label.setFillColor(Color::White);
    username_label.setPosition(200, 200);

    // username input box
    username_box.setSize(Vector2f(400, 45));
    username_box.setFillColor(Color(255, 255, 255, 50));
    username_box.setOutlineColor(Color::White);
    username_box.setOutlineColor(Color::Yellow);
    username_box.setOutlineThickness(2);
    username_box.setPosition(200, 230);

    // username typed text
    username_input.setFont(font);
    username_input.setCharacterSize(20);
    username_input.setFillColor(Color::White);
    username_input.setPosition(210, 238);

    // password ttile
    password_label.setFont(font);
    password_label.setString("Password:");
    password_label.setCharacterSize(22);
    password_label.setFillColor(Color::White);
    password_label.setPosition(200, 300);

    // password input box
    password_box.setSize(Vector2f(400, 45));
    password_box.setFillColor(Color(255, 255, 255, 50));
    password_box.setOutlineColor(Color::White);
    password_box.setOutlineThickness(2);
    password_box.setPosition(200, 330);

    // password typed text
    password_input.setFont(font);
    password_input.setCharacterSize(20);
    password_input.setFillColor(Color::White);
    password_input.setPosition(210, 338);

    //  button for login
    login_button.setSize(Vector2f(180, 50));
    login_button.setFillColor(Color(0, 150, 200));
    login_button.setPosition(200, 420);

    login_button_text.setFont(font);
    login_button_text.setString("Login");
    login_button_text.setCharacterSize(22);
    login_button_text.setFillColor(Color::White);
    login_button_text.setPosition(260, 430);

    //  button for register
    register_button.setSize(Vector2f(180, 50));
    register_button.setFillColor(Color(0, 180, 100));
    register_button.setPosition(420, 420);

    register_button_text.setFont(font);
    register_button_text.setString("Register");
    register_button_text.setCharacterSize(22);
    register_button_text.setFillColor(Color::White);
    register_button_text.setPosition(460, 430);

    // text for error
    error_text.setFont(font);
    error_text.setCharacterSize(18);
    error_text.setFillColor(Color::Red);
    error_text.setPosition(200, 490);
}

void LoginScreen::handle_input(Event& event, RenderWindow& window) {

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse_pos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        // check if username box clicked
        if (username_box.getGlobalBounds().contains(mouse_pos)) {
            active_box = 1;
            username_box.setOutlineColor(Color::Yellow);
            password_box.setOutlineColor(Color::White);
        }
        // check if password box clicked
        else if (password_box.getGlobalBounds().contains(mouse_pos)) {
            active_box = 2;
            password_box.setOutlineColor(Color::Yellow);
            username_box.setOutlineColor(Color::White);
        }

        // check if login button clicked
        else if (login_button.getGlobalBounds().contains(mouse_pos)) {
            if (auth.loginUser(username_str, password_str)) {
                is_logged_in = true;
                show_error = false;
            }
            else {
                show_error = true;
                error_message = "Wrong username or password!";
            }
        }

        //check if register button clicked
        else if (register_button.getGlobalBounds().contains(mouse_pos)) {
            if (username_str == "" || password_str == "") {
                show_error = true;
                error_message = "Please fill in both fields!";
            }
            else if (auth.registerUser(username_str, password_str)) {
                show_error = true;
                error_message = "Registered! Now login.";
                error_text.setFillColor(Color::Green);
            }
            else {
                show_error = true;
                error_message = "Username already taken!";
                error_text.setFillColor(Color::Red);
            }
        }
    }

    //handle keyboard typing
    if (event.type == Event::TextEntered) {

        // backspace
        if (event.text.unicode == 8) {
            if (active_box == 1 && username_str.length() > 0)
                username_str.pop_back();
            else if (active_box == 2 && password_str.length() > 0)
                password_str.pop_back();
        }
        // normal character
        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            char typed = static_cast<char>(event.text.unicode);
            if (active_box == 1)
                username_str += typed;
            else if (active_box == 2)
                password_str += typed;
        }
    }

    // update displayed text
    username_input.setString(username_str);

    // hiding password
    string stars = "";
    for (int i = 0; i < password_str.length(); i++)
        stars += "*";
    password_input.setString(stars);

    // update error message
    if (show_error)
        error_text.setString(error_message);
}

void LoginScreen::draw(RenderWindow& window) {
    window.draw(bg_sp);
    window.draw(password_box);
    window.draw(password_input);
    window.draw(login_button);
    window.draw(login_button_text);
    window.draw(register_button);
    window.draw(register_button_text);
    window.draw(title_text);
    window.draw(username_label);
    window.draw(username_box);
    window.draw(username_input);
    window.draw(password_label);
    if (show_error)
        window.draw(error_text);
}