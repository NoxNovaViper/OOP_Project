#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;


//to convert int into string
string intToStr(int num) {
    if (num == 0)
        return "0";
    string result = "";
    bool negative = false;

    if (num < 0)
    {
        negative = true;
        num = -num;
    }
    while (num > 0)
    {
        char digit = (num % 10) + '0';
        result = digit + result;
        num = num / 10;
    }

    if (negative)
        result = "-" + result;
    return result;
}

// converts string into int/number
int strToInt(const string& str) {
    int result = 0;
    bool negative = false;
    int x = 0;

    // check if negative
    if (str[0] == '-') {
        negative = true;
        x = 1;
    }
    //each char into digit
    while (x < str.length()) {
        result = result * 10 + (str[x] - '0');
        x++;
    }
    if (negative)
        result = -result;
    return result;
}

Database::Database() {}

// to save player progress 
void Database::saveProgress(const string& username, int level, int lives, int gems, int score) {

    ifstream file("SnowBrosAssets\Start\progress.txt");
    string Data = "";
    string line;
    bool found = false;

    // go through file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string savedUser;
        getline(ss, savedUser, '|');

        // to found our player 
        if (savedUser == username) {
            Data += username + "|" + intToStr(level) + "|" + intToStr(lives) + "|" +
                intToStr(gems) + "|" +
                intToStr(score) + "\n";
            found = true;
        }
        else {
            //  player not found
            Data += line + "\n";
        }
    }
    file.close();
    if (!found) {
        Data += username + "|" + intToStr(level) + "|" + intToStr(lives) + "|" +
            intToStr(gems) + "|" +
            intToStr(score) + "\n";
    }
    // writing everything 
    ofstream writefile("SnowBrosAssets\Start\progress.txt");
    writefile << Data;
    writefile.close();
}
// loading player progress from progress file
// finds player by username and fills their data
void Database::loadProgress(const string& username, int& level, int& lives,
    int& gems, int& score) {
    ifstream readFile("SnowBrosAssets\Start\progress.txt");
    string line;
    while (getline(readFile, line)) {
        stringstream ss(line);
        string savedUser, lvl, liv, gem, sc;

        getline(ss, savedUser, '|');
        getline(ss, lvl, '|');
        getline(ss, liv, '|');
        getline(ss, gem, '|');
        getline(ss, sc, '|');

        // found our player
        if (savedUser == username) {
            level = strToInt(lvl);
            lives = strToInt(liv);
            gems = strToInt(gem);
            score = strToInt(sc);
            readFile.close();
            return;
        }
    }
    readFile.close();

    // player not found give default values
    level = 1;
    lives = 2;
    gems = 0;
    score = 0;
}

// adding new score to leaderboard
void Database::saveLeaderboard(const string& username, int score, int level) {
    ofstream writeFile("SnowBrosAssets\Start\leaderboard.txt", ios::app);
    writeFile << username << "|"
        << intToStr(score) << "|"
        << intToStr(level) << "\n";
    writeFile.close();
}


void Database::displayLeaderboard() {
    ifstream readFile("SnowBrosAssets\Start\leaderboard.txt");
    // store all entries
    string usernames[100];
    int scores[100];
    int levels[100];
    int count = 0;
    string line;

    while (getline(readFile, line) && count <= 100) {
        stringstream ss(line);
        string username, score, level;

        getline(ss, username, '|');
        getline(ss, score, '|');
        getline(ss, level, '|');
        usernames[count] = username;
        scores[count] = strToInt(score);
        levels[count] = strToInt(level);
        //cout << count<< ". "<< usernames << " | Score: " << scores << " | Level: " << levels << endl;
        count++;
    }
    readFile.close();
    //bubble sorting
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {

                int a = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = a;

                int b = levels[j];
                levels[j] = levels[j + 1];
                levels[j + 1] = b;

                string c = usernames[j];
                usernames[j] = usernames[j + 1];
                usernames[j + 1] = c;
            }
        }
    }
    cout << "\n    ||||  LEADERBOARD TOP 10  ||||" << endl;
    for (int i = 0;i < 10;i++) {
        cout << i << ". " << usernames << " | Score: " << scores << " | Level: " << levels << endl;
    }
}