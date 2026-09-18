#include "MyLibrary.h"

vector<Employee*> employees;
vector<Product*> products;
vector<Transaction*> transactions;

const string EMPLOYEES_FILE = "data/employees.txt";
const string PRODUCTS_FILE = "data/products.txt";
const string TRANSACTIONS_FILE = "data/transactions.txt";

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    loadAllData();
    showMainMenu();
    saveAllData();

    return 0;
}