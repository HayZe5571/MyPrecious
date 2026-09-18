#include "MyLibrary.h"

bool isLoginValid(const string& login) {
    if (login.empty()) return false;
    if (login.find(' ') != string::npos) return false;
    return true;
}

bool isLoginUnique(const string& login) {
    for (auto employee : employees) {
        if (employee->getLogin() == login) {
            return false;
        }
    }
    return true;
}

Employee* loginUser(const string& login, const string& password) {
    for (auto employee : employees) {
        if (employee->getLogin() == login && verifyPassword(password, employee->getPasswordHash())) {
            return employee;
        }
    }
    return nullptr;
}