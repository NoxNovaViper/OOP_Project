#pragma once
#include <SFML/Graphics.hpp>
#include "AuthManager.h"
#include <string>
using namespace std;
using namespace sf;
class LoginScreen {
private:
    AuthManager auth;
    bool isLoggedIn;
    Texture bgTx;
    Sprite bgSp;
    // window font
    Font font;
    // background
    RectangleShape background;
    // title text
    Text titleText;
    // username box
    RectangleShape usernameBox;
    Text usernameLabel;
    Text usernameInput;
    // password box
    sf::RectangleShape passwordBox;
    sf::Text passwordLabel;
    sf::Text passwordInput;

    // buttons
    sf::RectangleShape loginButton;
    sf::Text loginButtonText;
    sf::RectangleShape registerButton;
    sf::Text registerButtonText;

    // error message
    sf::Text errorText;

    // stored input strings
    string usernameStr;
    string passwordStr;

    // which box is active
    // 1 = username box  2 = password box
    int activeBox;

    // show error or not
    bool showError;
    string errorMessage;

public:
    LoginScreen();
    void setup();
    void handleInput(Event& event, RenderWindow& window);
    void draw(RenderWindow& window);
    void setTitle(string t) {
        titleText.setString(t); }
    bool getIsLoggedIn() { 
        return isLoggedIn;}
    string getLoggedInUsername() { return auth.getLoggedInUser(); }
};