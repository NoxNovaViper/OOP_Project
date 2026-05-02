#include "AuthManager.h"
#include<fstream>
#include<sstream>
AuthManager::AuthManager() {
    isloginDone = false;
    userlogin = "";
}
string AuthManager::intTostring(int num) {

    string res;
    bool negative = false;
    if (num < 0)
        negative = true;
    while (num > 0)
    {
        char digit = num % 10 + '0';
        res += digit;
        num /= 10;
    }
    if (negative)
        res = '-' + res;
    return res;
}
int AuthManager::passwordlength(string password)
{
    count = 0;
    for (int i = 0;password[i] != '\0';i++)
        count++;

    return count;
}
string AuthManager::hashPassword(const string& password) {

    long int hash = 1234;
    passwordlength(password);
    for (int i = 0;i < count;i++) {
        char c = password[i];
        hash = 3 * hash + c;
    }
    return intTostring(hash);
}
bool AuthManager::registerUser(const string& username, const string& password) {
    // first check is username available
    ifstream readfile("SnowBrosAssets\Start\users.txt");
    string line;
    while (getline(readfile, line)) {
        stringstream ss(line);
        string savedUsername;
        getline(ss, savedUsername, '|');
        if (savedUsername == username) {
            readfile.close();
            return false; // current username is not available
        }
    }
    readfile.close();
    //current username is available
    ofstream writefile("SnowBrosAssets\Start\users.txt", ios::app);
    if (!writefile.is_open())
        return false;
    writefile << username << "|" << hashPassword(password) << "\n";
    writefile.close();
    return true;
}
bool AuthManager::loginUser(const string& username, const string& password) {

    ifstream readfile("SnowBrosAssets\Start\users.txt");
    if (!readfile.is_open()) return false;
    string line;
    string hashinput = hashPassword(password);

    while (getline(readfile, line)) {
        stringstream ss(line);
        string storedusername, storedhash;
        getline(ss, storedusername, '|');
        getline(ss, storedhash, '|');
        if (storedusername == username && storedhash == hashinput) {
            readfile.close();
            isloginDone = true;
            userlogin = username;
            return true; // login completed
        }
    }

    readfile.close();
    return false; // login not found

}
void AuthManager::logout() {
    isloginDone = false;
    userlogin = "";
}