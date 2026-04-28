#pragma once
#include <string>
#include<iostream>
#include<fstream>
using namespace std;
class AuthManager {
private:
    string userlogin;
    bool isloginDone;
    int count = 0;

public:
    AuthManager();
    string hashPassword(const string& password);
    bool registerUser(const string& username, const string& password);
    bool loginUser(const string& username, const string& password);
    void logout();
    string intTostring(int num);
    int passwordlength(string);
    bool getIsLoggedIn() const {
        return isloginDone;
    }
    string getLoggedInUser() const {
        return userlogin;
    }
};