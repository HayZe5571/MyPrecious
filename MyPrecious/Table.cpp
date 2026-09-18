#include "MyLibrary.h"

void printEmployeesTable(bool showId, bool showIsActive) {
    printEmployeesTable(employees, showId, showIsActive);
}

void printProductsTable(bool showId, bool showStatus) {
    printProductsTable(products, showId, showStatus);
}

void printEmployeesTable(const vector<Employee*>& empList, bool showId, bool showIsActive) {
    vector<Employee*> managers;
    for (auto employee : empList) {
        if (employee->getRole() == "manager") {
            managers.push_back(employee);
        }
    }

    cout << setw(4) << left << "№"
        << setw(15) << left << "Логин"
        << setw(15) << left << "Имя"
        << setw(21) << left << "Фамилия";

    if (showId) {
        cout << setw(7) << left << "ID";
    }

    if (showIsActive) {
        cout << setw(10) << left << "Статус";
    }

    cout << endl;

    int totalWidth = 4 + 15 + 15 + 21;
    if (showId) totalWidth += 7;
    if (showIsActive) totalWidth += 10;

    cout << string(totalWidth, '-') << endl;

    int counter = 1;
    for (auto manager : managers) {
        cout << setw(3) << left << counter++ << " ";
        manager->printTable(showId, showIsActive);
    }

    cout << endl;
}

void printProductsTable(const vector<Product*>& prodList, bool showId, bool showStatus) {
    cout << setw(4) << left << "№";

    if (showId) {
        cout << setw(7) << left << "ID";
    }

    cout << setw(36) << left << "Название"
        << setw(10) << left << "Категория"
        << setw(21) << left << "Материалы"
        << setw(16) << left << "Камни"
        << setw(10) << left << "Цена";

    if (showStatus) {
        cout << setw(10) << left << "Статус";
    }

    cout << endl;

    int totalWidth = 4 + 36 + 10 + 21 + 16 + 10;
    if (showId) totalWidth += 7;
    if (showStatus) totalWidth += 10;

    cout << string(totalWidth, '-') << endl;

    int counter = 1;
    for (auto product : prodList) {
        cout << setw(3) << left << counter++ << " ";
        product->printTable(showId, showStatus);
    }

    cout << endl;
}

void printTransactionsTable() {
    cout << setw(4) << left << "№"
        << setw(7) << left << "ID чек"
        << setw(20) << left << "Дата/время"
        << setw(12) << left << "Менеджер"
        << setw(20) << left << "Клиент"
        << setw(15) << left << "Телефон"
        << setw(10) << left << "Сумма"
        << setw(7) << left << "ID"
        << setw(33) << left << "Наименование"
        << setw(10) << left << "Цена" << endl;

    cout << string(138, '-') << endl;

    int counter = 1;
    for (auto transaction : transactions) {
        vector<int> productIds = transaction->getProductIds();
        vector<string> productNames = transaction->getProductNames();
        vector<double> productPrices = transaction->getProductPrices();

        if (!productIds.empty()) {
            cout << setw(4) << left << counter++ << ""
                << setw(7) << left << transaction->getId()
                << setw(20) << left << transaction->getDateTime()
                << setw(12) << left << transaction->getEmployeeLogin()
                << setw(20) << left << (transaction->getClientFullName().length() > 18 ?
                    transaction->getClientFullName().substr(0, 15) + "..." : transaction->getClientFullName())
                << setw(15) << left << transaction->getClientPhone()
                << setw(10) << left << fixed << setprecision(2) << transaction->getTotalPrice()
                << setw(7) << left << productIds[0]
                << setw(33) << left << (productNames[0].length() > 30 ?
                    productNames[0].substr(0, 27) + "..." : productNames[0])
                << setw(10) << left << fixed << setprecision(2) << productPrices[0] << endl;

            for (size_t i = 1; i < productIds.size(); i++) {
                cout << setw(4) << left << ""
                    << setw(7) << left << ""
                    << setw(20) << left << ""
                    << setw(12) << left << ""
                    << setw(20) << left << ""
                    << setw(15) << left << ""
                    << setw(10) << left << ""
                    << setw(7) << left << productIds[i]
                    << setw(33) << left << (productNames[i].length() > 30 ?
                        productNames[i].substr(0, 27) + "..." : productNames[i])
                    << setw(10) << left << fixed << setprecision(2) << productPrices[i] << endl;
            }
        }
        else {
            cout << setw(4) << left << counter++
                << setw(7) << left << transaction->getId()
                << setw(20) << left << transaction->getDateTime()
                << setw(12) << left << transaction->getEmployeeLogin()
                << setw(20) << left << (transaction->getClientFullName().length() > 18 ?
                    transaction->getClientFullName().substr(0, 15) + "..." : transaction->getClientFullName())
                << setw(15) << left << transaction->getClientPhone()
                << setw(10) << left << fixed << setprecision(2) << transaction->getTotalPrice()
                << setw(7) << left << ""
                << setw(33) << left << ""
                << setw(10) << left << "" << endl;
        }
    }

    cout << endl;
}

vector<Employee*> filterEmployees(const vector<Employee*>& source, int filterType) {
    vector<Employee*> result;
    for (auto employee : source) {
        if (employee->getRole() != "manager") continue;

        bool include = false;
        if (filterType == 1) {
            include = employee->getIsActive();
        }
        else if (filterType == 2) {
            include = !employee->getIsActive();
        }

        if (include) {
            result.push_back(employee);
        }
    }
    return result;
}

vector<Product*> filterProducts(const vector<Product*>& source, int filterType) {
    vector<Product*> result;
    for (auto product : source) {
        bool include = false;
        if (filterType == 1) {
            include = product->getStatus();
        }
        else if (filterType == 2) {
            include = !product->getStatus();
        }

        if (include) {
            result.push_back(product);
        }
    }
    return result;
}

void sortEmployees(vector<Employee*>& empList) {
    sort(empList.begin(), empList.end(),
        [](Employee* a, Employee* b) {
            if (a->getLastName() != b->getLastName()) {
                return a->getLastName() < b->getLastName();
            }
            return a->getFirstName() < b->getFirstName();
        });
}

void sortProductsByCategory(vector<Product*>& prodList) {
    sort(prodList.begin(), prodList.end(),
        [](Product* a, Product* b) {
            return a->getCategory() < b->getCategory();
        });
}

void sortProductsByPrice(vector<Product*>& prodList) {
    sort(prodList.begin(), prodList.end(),
        [](Product* a, Product* b) {
            return a->getPrice() > b->getPrice();
        });
}