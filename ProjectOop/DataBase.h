#pragma once
#include<string>
using namespace std;
class Database {
public:
    Database();

    void save_progress(const string& username, int level, int lives,
        int gems, int score);
    void load_progress(const string& username, int& level, int& lives,
        int& gems, int& score);
    void save_leaderboard(const string& username,
        int score, int level);
    void display_leaderboard();
    void load_leaderboard(string usernames[], int scores[], int levels[], int& count);
};