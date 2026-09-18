#pragma once

extern string hashPassword(const string& password);
extern bool verifyPassword(const string& password, const string& passwordHash);
extern bool isPasswordValid(const string& password);