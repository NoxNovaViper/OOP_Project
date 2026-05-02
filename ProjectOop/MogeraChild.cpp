#include "MogeraChild.h"
#include "AssetLoader.h"
#include <cstdlib>

MogeraChild::MogeraChild(float startX, float startY) {
    x = startX;
    y = startY;
    hp = 1; 
    speed = 120.0f;
    gemdrop = 5;
    // Pick a random initial direction
    directionX = (rand() % 2 == 0) ? 1.0f : -1.0f;
}

void MogeraChild::update(float deltaTime) {
    if (Rolling) {
        x += Roll_speed * deltaTime;
        if (x < 0) x = 800;
        if (x > 800) x = 0;
        return;
    }
    if (update_snow_state(deltaTime)) {
        return;
    }

    // Moves in one direction until it hits a wall
    x += directionX * speed * snow_speed_multiplier() * deltaTime;
    
    // Bounce off walls
    if (x <= 0) {
        x = 0;
        directionX = 1.0f;
    } else if (x >= 752) { // 800 - 48 sprite width
        x = 752;
        directionX = -1.0f;
    }

    // Use shared gravity from base class
    applyGravity(deltaTime);
}

void MogeraChild::draw(sf::RenderWindow& window) {
    sf::Sprite s;
    // We can reuse botom texture or flyng texture, since we don't have a specific sprite
    s.setTexture(Assets::botom_t);
    int frameSize = Assets::botom_t.getSize().y;
    s.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    s.setPosition(x, y);
    // Smaller sprite
    s.setScale(20.0f / frameSize, 20.0f / frameSize);
    
    // Color it differently so the player knows it's a child
    s.setColor(sf::Color(255, 100, 100)); 
    window.draw(s);
    drawSnowOverlay(window, 20.0f, 20.0f);
}

void MogeraChild::hit() {
    add_snow(50);
}
