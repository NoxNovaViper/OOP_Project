#pragma once
#include<string>
class Database {
public:
    Database();

    void saveProgress(const std::string& username, int level, int lives,
        int gems, int score);
    void loadProgress(const std::string& username, int& level, int& lives,
        int& gems, int& score);
    void saveLeaderboard(const std::string& username,
        int score, int level);
    void displayLeaderboard();
};