#pragma once

extern bool isLoginValid(const string& login);
extern bool isLoginUnique(const string& login);
extern Employee* loginUser(const string& login, const string& password);