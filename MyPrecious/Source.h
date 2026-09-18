#pragma once

extern bool isValidName(const string& str);
extern bool isValidName(const string& str);
extern bool validatePhone(const string& phone);
extern string inputPhone(const string& prompt);

extern int generateUniqueId();
extern string getCurrentDateTime();

extern string toLower(const string& str);
extern vector<string> splitString(const string& str, char delimiter);
template<typename T>
extern string joinString(const vector<T>& vec, char delimiter);
extern bool danetka(const string& prompt);

extern string chooseFromList(const vector<string>& options, const string& prompt);
extern vector<int> chooseMultipleFromList(const vector<string>& options, const string& prompt);

template<typename T>
extern T chek(const string& prompt, const string& error, function<bool(T)> customCheck);