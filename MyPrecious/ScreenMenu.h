#pragma once

extern void showMainMenu();
extern void showLoginScreen();
extern void showRegistrationScreen();
extern void showAdminMenu(Employee* admin);
extern void showManagerMenu(Employee* manager);
extern void showAdminProductsMenu();
extern void showAdminManagersMenu();
extern void showManagerProductsMenu();
extern void showManagerManagersMenu();
extern void printHeader(const string& title);