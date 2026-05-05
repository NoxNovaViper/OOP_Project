#pragma once
#include <SFML/Graphics.hpp>
#include "AuthManager.h"
#include <string>
using namespace std;
using namespace sf;
class LoginScreen {
private:
    AuthManager auth;
    bool is_logged_in;
    Texture bg_tx;
    Sprite bg_sp;
    // window font
    Font font;
    // background
    RectangleShape background;
    // title text
    Text title_text;
    // username box
    RectangleShape username_box;
    Text username_label;
    Text username_input;
    // password box
    RectangleShape password_box;
    Text password_label;
    Text password_input;

    // buttons
    RectangleShape login_button;
    Text login_button_text;
    RectangleShape register_button;
    Text register_button_text;

    // error message
    Text error_text;

    // stored input strings
    string username_str;
    string password_str;

    // which box is active
    // 1 = username box  2 = password box
    int active_box;

    // show error or not
    bool show_error;
    string error_message;

public:
    LoginScreen();
    void set_up();
    void handle_input(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);
    void set_title(string title) {
        title_text.setString(title);
    }
    bool get_is_logged_in() {
        return is_logged_in;
    }
    string get_logged_in_username() { return auth.getLoggedInUser(); }
};