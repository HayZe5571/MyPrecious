#include "MyLibrary.h"

void saveAllData() {
    saveEmployees();
    saveProducts();
    saveTransactions();

    for (auto employee : employees) delete employee;
    for (auto product : products) delete product;
    for (auto transaction : transactions) delete transaction;

    employees.clear();
    products.clear();
    transactions.clear();
}

void loadAllData() {
    loadEmployees();
    loadProducts();
    loadTransactions();
}

void saveEmployees() {
    ofstream file(EMPLOYEES_FILE);
    if (!file.is_open()) return;

    for (auto employee : employees) {
        employee->saveToFile(file);
    }
    file.close();
}

void saveProducts() {
    ofstream file(PRODUCTS_FILE);
    if (!file.is_open()) return;

    for (auto product : products) {
        product->saveToFile(file);
    }
    file.close();
}

void saveTransactions() {
    ofstream file(TRANSACTIONS_FILE);
    if (!file.is_open()) return;

    for (auto transaction : transactions) {
        transaction->saveToFile(file);
    }
    file.close();
}

void loadEmployees() {
    ifstream file(EMPLOYEES_FILE);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        vector<string> fields = splitString(line, ';');
        Employee* employee = new Employee();
        employee->loadFromFile(fields);
        employees.push_back(employee);
    }
    file.close();
}

void loadProducts() {
    ifstream file(PRODUCTS_FILE);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        vector<string> fields = splitString(line, ';');
        Product* product = new Product();
        product->loadFromFile(fields);
        products.push_back(product);
    }
    file.close();
}

void loadTransactions() {
    ifstream file(TRANSACTIONS_FILE);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        vector<string> fields = splitString(line, ';');
        Transaction* transaction = new Transaction();
        transaction->loadFromFile(fields);
        transactions.push_back(transaction);
    }
    file.close();
}