#include "MyLibrary.h"

string hashPassword(const string& password) {
    size_t hashValue = 0;
    const size_t prime = 31;

    for (char c : password) {
        hashValue = hashValue * prime + c;
    }

    stringstream ss;
    ss << hex << hashValue;
    return ss.str();
}

bool verifyPassword(const string& password, const string& passwordHash) {
    string hashedInput = hashPassword(password);
    return hashedInput == passwordHash;
}

bool isPasswordValid(const string& password) {
    return password.length() >= 4;
}