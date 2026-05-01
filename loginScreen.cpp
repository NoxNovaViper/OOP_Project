
#include "LoginScreen.h"

using namespace sf;
LoginScreen::LoginScreen() {
    isLoggedIn = false;
    activeBox = 0; // cursor on username 
   
    showError = false;
    usernameStr = "";
    passwordStr = "";
    errorMessage = "";
}

void LoginScreen::setup() {
    
    // loading font
    font.loadFromFile("arial.ttf");

    
    // background 
    bgTx.loadFromFile("BG.png");

    bgSp.setTexture(bgTx);
    bgSp.setScale(
        800.0f / bgTx.getSize().x,
        600.0f / bgTx.getSize().y
    );
    
    titleText.setFont(font);
    titleText.setString("Snow Bros");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::White);
    titleText.setPosition(300, 60);

    // username title
    usernameLabel.setFont(font);
    usernameLabel.setString("Username:");
    usernameLabel.setCharacterSize(22);
    usernameLabel.setFillColor(Color::White);
    usernameLabel.setPosition(200, 200);

    // username input box
    usernameBox.setSize(Vector2f(400, 45));
    usernameBox.setFillColor(Color(255, 255, 255, 50));
    usernameBox.setOutlineColor(Color::White);
    usernameBox.setOutlineColor(Color::Yellow);
    usernameBox.setOutlineThickness(2);
    usernameBox.setPosition(200, 230);

    // username typed text
    usernameInput.setFont(font);
    usernameInput.setCharacterSize(20);
    usernameInput.setFillColor(Color::White);
    usernameInput.setPosition(210, 238);

    // password ttile
    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(22);
    passwordLabel.setFillColor(Color::White);
    passwordLabel.setPosition(200, 300);

    // password input box
    passwordBox.setSize(Vector2f(400, 45));
    passwordBox.setFillColor(Color(255, 255, 255, 50));
    passwordBox.setOutlineColor(Color::White);
    passwordBox.setOutlineThickness(2);
    passwordBox.setPosition(200, 330);

    // password typed text
    passwordInput.setFont(font);
    passwordInput.setCharacterSize(20);
    passwordInput.setFillColor(Color::White);
    passwordInput.setPosition(210, 338);

    //  button for login
    loginButton.setSize(Vector2f(180, 50));
    loginButton.setFillColor(Color(0, 150, 200));
    loginButton.setPosition(200, 420);

    loginButtonText.setFont(font);
    loginButtonText.setString("Login");
    loginButtonText.setCharacterSize(22);
    loginButtonText.setFillColor(Color::White);
    loginButtonText.setPosition(260, 430);

    //  button for register
    registerButton.setSize(Vector2f(180, 50));
    registerButton.setFillColor(Color(0, 180, 100));
    registerButton.setPosition(420, 420);

    registerButtonText.setFont(font);
    registerButtonText.setString("Register");
    registerButtonText.setCharacterSize(22);
    registerButtonText.setFillColor(Color::White);
    registerButtonText.setPosition(460, 430);

    // text for error
    errorText.setFont(font);
    errorText.setCharacterSize(18);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(200, 490);
}

void LoginScreen::handleInput(Event& event, RenderWindow& window) {

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(
            Vector2i(event.mouseButton.x, event.mouseButton.y)
        );

        // check if username box clicked
        if (usernameBox.getGlobalBounds().contains(mousePos)) {
            activeBox = 0;
            // reflecting active box
            usernameBox.setOutlineColor(Color::Yellow);
            passwordBox.setOutlineColor(Color::White);
        }

        // check if password box clicked
        else if (passwordBox.getGlobalBounds().contains(mousePos)) {
            activeBox = 2;
            passwordBox.setOutlineColor(Color::Yellow);
            usernameBox.setOutlineColor(Color::White);
        }

        // check if login button clicked
        else if (loginButton.getGlobalBounds().contains(mousePos)) {
            if (auth.loginUser(usernameStr, passwordStr)) {
                isLoggedIn = true;
                showError = false;
            }
            else {
                showError = true;
                errorMessage = "Wrong username or password!";
            }
        }

        // check if register button clicked
        else if (registerButton.getGlobalBounds().contains(mousePos)) {
            if (usernameStr == "" || passwordStr == "") {
                showError = true;
                errorMessage = "Please fill in both fields!";
            }
            else if (auth.registerUser(usernameStr, passwordStr)) {
                showError = true;
                errorMessage = "Registered! Now login.";
                errorText.setFillColor(Color::Green);
            }
            else {
                showError = true;
                errorMessage = "Username already taken!";
                errorText.setFillColor(Color::Red);
            }
        }
    }

    // handle keyboard typing
    if (event.type == Event::TextEntered) {

        // backspace
        if (event.text.unicode == 8) {
            if (activeBox == 1 && usernameStr.length() > 0)
                usernameStr.pop_back();
            else if (activeBox == 2 && passwordStr.length() > 0)
                passwordStr.pop_back();
        }
        // normal character
        else if (event.text.unicode < 128) {
            char typed = static_cast<char>(event.text.unicode);
            if (activeBox == 1)
                usernameStr += typed;
            else if (activeBox == 2)
                passwordStr += typed;
        }
    }

    // update displayed text
    usernameInput.setString(usernameStr);

    // hiding password
    string stars = "";
    for (int i = 0; i < passwordStr.length(); i++)
        stars += "*";
    passwordInput.setString(stars);

    // update error message
    if (showError)
        errorText.setString(errorMessage);
}

void LoginScreen::draw(RenderWindow& window) {
    window.draw(bgSp);
    window.draw(passwordBox);
    window.draw(passwordInput);
    window.draw(loginButton);
    window.draw(loginButtonText);
    window.draw(registerButton);
    window.draw(registerButtonText);
    window.draw(titleText);
    window.draw(usernameLabel);
    window.draw(usernameBox);
    window.draw(usernameInput);
    window.draw(passwordLabel);
    if (showError)
        window.draw(errorText);
}