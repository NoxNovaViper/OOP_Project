
#include "Player.h"
#include<ctime>
#include<cstdlib>
Player::Player(float startX, float startY, int playerNum, int charactype) {
    x = startX;
    y = startY;
    lives = 2;
    score = 0;
    gemCount = 0;
    isalive = true;
    playerNumber = playerNum;
    chaincount = 0;
    speed = 100.0f;
    snowballPower = 1.0f;
    snowballDistance = 600.0f;

    if (charactype == 1)  //nick
    {
        name = "Nick";
        speed = 100.0f;
        snowballPower = 1.0f;
        snowballDistance = 600.0f;
    }
    else if (charactype == 2)
    {
        name = "Tom";
        speed = 200.0f;
        snowballPower = 1.0f;
        snowballDistance = 500.0f;
    }
    else if (charactype == 3)
    {
        name = "Bob";
        speed = 150.0f;
        snowballPower = 1.0f;
        snowballDistance = 550.0f;
    }
}
void Player::activateSpeedboost() {
    speedboostActive = true;
    speedboostTimer = 15.0f;  // lasts 15 seconds
    speed = speed * 1.5f;
}

void Player::activateSnowballpower() {
    snowballpowerActive = true;  // lasts until level end
    snowballPower = 2.0f;
}
void Player::activateDistanceincreased() {
    distanceincreaseActive = true;  // lasts until level end
    snowballDistance = 800.0f;
}

void Player::activateBalloonmode() {
    balloonmodeActive = true;
    balloonmodeTimer = 10.0f;  // lasts 10 seconds
}

void Player::enemykilled(int enemyType) {
    int points = 0;
    if (enemyType == 1)       // Botom
        points = 100 + rand() % 401;
    else if (enemyType == 2)  // Flyngfooga
        points = 200 + rand() % 601;
    else if (enemyType == 3)  // Tornado
        points = 300 + rand() % 901;
    else if (enemyType == 4)  // Mogera
        points = 5000;
    else if (enemyType == 5)  // Gamakichi
        points = 10000;
    if (chaincount > 0)
        points = points + (points * chaincount * 10 / 100);
    score += points;
    chaincount++;
}
void Player::chainreset() {
    chaincount = 0;
}

bool Player::spendgems(int amount) {
    if (gemCount >= amount) {
        gemCount -= amount;
        return true;
    }
    return false;
}
void Player::update(float deltaTime) {}
void Player::draw() {}
void Player::snowballThrough() {}
void Player::takeDamage() {
    lives--;
    if (lives <= 0)
        isalive = false;
}
void Player::pickGem(int amount) {
    gemCount += amount;
}
void Player::pickPowerUp() {}

//Getters for player attributes
string Player::get_name() { return name; }
Sprite& Player::get_sprite() { return sprite; }
Texture& Player::get_texture() { return texture; }
FloatRect& Player::get_hitbox() { return hitbox; }
int Player::get_cur_frame() { return cur_frame; }
float Player::get_vy() { return vy; }
bool Player::get_on_ground() { return on_ground; }
float Player::get_jump_power() { return jump_power; }

//Getters for player stats
float Player::get_x() { return x; }
float Player::get_y() { return y; }
int Player::get_lives() { return lives; }
int Player::get_score() { return score; }
int Player::get_gemCount() { return gemCount; }
float Player::get_speed() { return speed; }
float  Player::get_snowballPower() { return snowballPower; }
float Player::get_snowballDistance() { return snowballDistance; }
float Player::get_balloonmodeTimer() { return balloonmodeTimer; }
float Player::get_speedboostTimer() { return speedboostTimer; }
bool Player::get_isalive() { return isalive; }
int Player::get_playerNumber() { return playerNumber; }
int Player::get_chaincount() { return chaincount; }
bool Player::get_speedboostActive() { return speedboostActive; }
bool Player::get_snowballpowerActive() { return snowballpowerActive; }
bool Player::get_distanceincreaseActive() { return distanceincreaseActive; }
bool Player::get_balloonmodeActive() { return balloonmodeActive; }


//setters for player attributes
void Player::set_name(string new_name) { name = new_name; }
void Player::set_sprite(Sprite s) { sprite = s; }
void Player::set_texture(Texture t) { texture = t; }
void Player::set_hitbox(FloatRect h) { hitbox = h; }
void Player::set_cur_frame(int new_frame) { cur_frame = new_frame; }
void Player::set_vy(float new_vy) { vy = new_vy; }
void Player::set_on_ground(bool new_on_ground) { on_ground = new_on_ground; }
void Player::set_jump_power(float new_jump_power) { jump_power = new_jump_power; }

//stters for player stats
void Player::set_x(float new_x) { x = new_x; }
void Player::set_y(float new_y) { y = new_y; }
void Player::set_lives(int l) { lives = l; }
void Player::set_score(int s) { score = s; }
void Player::set_gemCount(int g) { gemCount = g; }
void Player::set_speed(float s) { speed = s; }
void Player::set_snowballPower(float b) { snowballPower = b; }
void Player::set_snowballDistance(float D) { snowballDistance = D; }
void Player::set_balloonmodeTimer(float b) { balloonmodeTimer = b; }
void Player::set_speedboostTimer(float b) { speedboostTimer = b; }
void Player::set_isalive(bool a) { isalive = a; }
void Player::set_playerNumber(int num) { playerNumber = num; }
void Player::set_chaincount(int c) { chaincount = c; }
void Player::set_speedboostActive(bool s) { speedboostActive = s; }
void Player::set_snowballpowerActive(bool s) { snowballpowerActive = s; }
void Player::set_distanceincreaseActive(bool s) { distanceincreaseActive = s; }
void Player::set_balloonmodeActive(bool s) { balloonmodeActive = s; }