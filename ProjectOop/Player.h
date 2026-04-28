#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;
class Player {
private:
    float x;
    float y;
    int lives;
    int score;
    int gemCount;
    float speed;
    float snowballPower;
    float snowballDistance;
    float balloonmodeTimer;
    float speedboostTimer;
    bool isalive;
    int playerNumber;
    int chaincount;
    bool speedboostActive;
    bool snowballpowerActive;
    bool distanceincreaseActive;
    bool balloonmodeActive;


public:
    string name;
    Sprite sprite;
    Texture texture;
    FloatRect hitbox;
    int cur_frame = 0;
    float vy = 0;
    bool on_ground = false;
    float jump_power = 900.0f;



	//Getters for player attributes
    string get_name();
    Sprite& get_sprite();
    Texture& get_texture();
    FloatRect& get_hitbox();
    int get_cur_frame();
    float get_vy();
    bool get_on_ground();
    float get_jump_power(); 

	//Getters for player stats
    float get_x();
    float get_y();
    int get_lives();
    int get_score();
    int get_gemCount();
    float get_speed();
    float  get_snowballPower();
    float get_snowballDistance();
    float get_balloonmodeTimer();
    float get_speedboostTimer();
    bool get_isalive();
    int get_playerNumber();
    int get_chaincount();
    bool get_speedboostActive();
    bool get_snowballpowerActive();
    bool get_distanceincreaseActive();
    bool get_balloonmodeActive();


	//setters for player attributes
    void set_name(string new_name);
    void set_sprite(Sprite s);
    void set_texture(Texture t);
    void set_hitbox(FloatRect h);
    void set_cur_frame(int new_frame);
    void set_vy(float new_vy);
    void set_on_ground(bool new_on_ground);
    void set_jump_power(float new_jump_power);

	//stters for player stats
    void set_x(float new_x);
    void set_y(float new_y);
    void set_lives(int l);
    void set_score(int s);
    void set_gemCount(int g);
    void set_speed(float s);
    void set_snowballPower(float b);
    void set_snowballDistance(float D);
    void set_balloonmodeTimer(float b);
    void set_speedboostTimer(float b);
    void set_isalive(bool a);
    void set_playerNumber(int num);
    void set_chaincount(int c);
    void set_speedboostActive(bool s);
    void set_snowballpowerActive(bool s);
    void set_distanceincreaseActive(bool s);
    void set_balloonmodeActive(bool s);

    Player(float startX, float startY, int playerNum, int charactype);
    void update(float deltaTime);
    void draw();
    void snowballThrough();
    void takeDamage();
    void pickGem(int amount);
    void pickPowerUp();
    bool spendgems(int amount);
    void enemykilled(int enemyType);
    void chainreset();
    void activateSpeedboost();
    void activateSnowballpower();
    void activateDistanceincreased();
    void activateBalloonmode();

    int getLives() const {
        return lives;
    }
    int getScore() const {
        return score;
    }
    int getGemCount() const {
        return gemCount;
    }
    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
    bool getIsAlive() const {
        return isalive;
    }
};