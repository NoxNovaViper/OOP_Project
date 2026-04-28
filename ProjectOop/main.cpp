#include <SFML/Graphics.hpp>
#include "Attack.h"
#include "Enemy_AI.h"
#include "InputHandler.h"
#include "Physics.h"
#include "LevelManager.h"
#include "Player.h"
#include "Animations.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
    Level_Manager manager;
    manager.next_level();

    // Constructor handles initialization, but we set starting positions here
    Player p1(200, 300, 1, 1), p2(600, 300, 2, 1);

    // P1 Initialization using Setters
    p1.set_x(200); p1.set_y(300);
    p1.set_vy(0);
    p1.set_hitbox(FloatRect(p1.get_x(), p1.get_y(), 30, 50));

    // P2 Initialization using Setters
    p2.set_x(600); p2.set_y(300);
    p2.set_vy(0);
    p2.set_hitbox(FloatRect(p2.get_x(), p2.get_y(), 30, 50));

    load_assets(p1);
    load_assets(p2);

    // Clock
    Clock gameClock;
    Font font;
    if (!font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf")) {
        cout << "Rip";
        return 0;
    }

    Text t1_t, t2_t, t3_t;
    t1_t.setString("Nick");
    t2_t.setString("Tom");
    t3_t.setString("Bob");
    t1_t.setFont(font);
    t2_t.setFont(font);
    t3_t.setFont(font);
    t1_t.setFillColor(Color::White);
    t2_t.setFillColor(Color::White);
    t3_t.setFillColor(Color::White);
    t1_t.setCharacterSize(24);
    t2_t.setCharacterSize(24);
    t3_t.setCharacterSize(24);
    t1_t.setPosition(300, 200);
    t2_t.setPosition(300, 300);
    t3_t.setPosition(300, 400);

    Texture BG_T;
    if (!BG_T.loadFromFile("SnowBrosAssets/Level1/bg.jpg")) {
        cout << "couldnt load bg" << endl;
    }
    Sprite BG_S;
    BG_S.setTexture(BG_T);
    BG_S.setScale(800.0f / BG_T.getSize().x, 600.0f / BG_T.getSize().y);

    while (window.isOpen())
    {
        float deltaTime = gameClock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            Inputhandle(event, manager, window, p1, p2);
        }

        bool p1_left = false, p1_right = false;
        bool p2_left = false, p2_right = false;

        if (!manager.get_pause()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                p_move(p1, -p1.get_speed(), deltaTime, true);
                p1_left = true;
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::D)) {
                p_move(p1, p1.get_speed(), deltaTime, true);
                p1_right = true;
            }

            if (sf::Keyboard::isKeyPressed(Keyboard::Num4)) {
                p_move(p2, -p2.get_speed(), deltaTime, true);
                p2_left = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
                p_move(p2, p2.get_speed(), deltaTime, true);
                p2_right = true;
            }

            // P1 Physics using Getters/Setters
            Gravity(p1, 980.0f, deltaTime);
            Position_change(p1, true, p1.get_vy(), deltaTime, false);
            // Assuming horizontal velocity is handled by p_move in InputHandler or similar logic

            // Update Hitbox
            FloatRect h1 = p1.get_hitbox();
            h1.left = p1.get_x();
            h1.top = p1.get_y();
            p1.set_hitbox(h1);

            // P2 Physics using Getters/Setters
            Gravity(p2, 980.0f, deltaTime);
            Position_change(p2, true, p2.get_vy(), deltaTime, false);

            // Update Hitbox
            FloatRect h2 = p2.get_hitbox();
            h2.left = p2.get_x();
            h2.top = p2.get_y();
            p2.set_hitbox(h2);

            // Simple Ground Collision
            if (p1.get_y() > 500) {
                p1.set_y(500);
                p1.set_vy(0);
                p1.set_on_ground(true);
            }
            else { p1.set_on_ground(false); }

            if (p2.get_y() > 500) {
                p2.set_y(500);
                p2.set_vy(0);
                p2.set_on_ground(true);
            }
            else { p2.set_on_ground(false); }
        }

        window.clear(Color::Black);
        window.draw(BG_S);

        // P1 Visuals
        RectangleShape p1Rect(Vector2f(p1.get_hitbox().width, p1.get_hitbox().height));
        p1Rect.setPosition(p1.get_x(), p1.get_y());
        p1Rect.setFillColor(Color::Green);
        window.draw(p1Rect);
        p1.get_sprite().setPosition(p1.get_x(), p1.get_y());
        window.draw(p1.get_sprite());

        // P2 Visuals
        RectangleShape p2Rect(Vector2f(p2.get_hitbox().width, p2.get_hitbox().height));
        p2Rect.setPosition(p2.get_x(), p2.get_y());
        p2Rect.setFillColor(Color::Blue);
        window.draw(p2Rect);

        update_animations(p1, deltaTime, p1_left, p1_right);
        update_animations(p2, deltaTime, p2_left, p2_right);

        window.draw(p1.get_sprite()); 
        window.draw(p2.get_sprite());

        if (manager.get_current_level() != nullptr) {
            debug_view(manager, p1.get_hitbox(), manager.get_current_level()->platforms, manager.get_current_level()->num_platforms, window);
            debug_view(manager, p2.get_hitbox(), manager.get_current_level()->platforms, 0, window);
        }

        window.display();
    }

    return 0;
}