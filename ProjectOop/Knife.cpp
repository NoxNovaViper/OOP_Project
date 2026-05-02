#include "Knife.h"
#include "AssetLoader.h"
#include <cmath>

Knife::Knife(float startX, float startY, float targetX, float targetY) {

    x = startX;
    y = startY;
    damage = 1.0f;
    isactive = true;
    float dx = targetX - startX;
    float dy = targetY - startY;
    float length = sqrt(dx * dx + dy * dy);
    if (length == 0.0f) {
        speedX = 0.0f;
        speedY = 0.0f;
    }
    else {
        speedX = (dx / length) * 150.0f;
        speedY = (dy / length) * 150.0f;
    }
}

void Knife::update(float deltaTime) {
    if (!isactive) {
        return;
    }

    x += speedX * deltaTime;
    y += speedY * deltaTime;

    if ((x < 0.0f) || (x > 800.0f) || (y < 0.0f) || (y > 600.0f)) {
        isactive = false;
    }
}
void Knife::draw(sf::RenderWindow& window) {
    if (Assets::knife_t.getSize().x > 0 && Assets::knife_t.getSize().y > 0) {
        sf::Sprite knifeSprite;
        knifeSprite.setTexture(Assets::knife_t);
        knifeSprite.setPosition(x, y);
        knifeSprite.setScale(24.0f / Assets::knife_t.getSize().x, 12.0f / Assets::knife_t.getSize().y);
        window.draw(knifeSprite);
    }
    else {
        sf::RectangleShape projShape(sf::Vector2f(15, 5));
        projShape.setPosition(x, y);
        projShape.setFillColor(sf::Color::White);
        window.draw(projShape);
    }
}
