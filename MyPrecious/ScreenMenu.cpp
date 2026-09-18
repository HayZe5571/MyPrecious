#include "MyLibrary.h"

void printHeader(const string& title) {
    system("cls");
    int titleLength = title.length();

    cout << "####" << string(titleLength, '#') << "####" << endl;
    cout << "#   " << title << "   #" << endl;
    cout << "####" << string(titleLength, '#') << "####" << endl << endl;
}

void showMainMenu() {
    while (true) {
        printHeader("ГЛАВНОЕ МЕНЮ");

        cout << "1. Регистрация" << endl;
        cout << "2. Авторизация" << endl;
        cout << "3. Выход" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор",
            [](int x) { return x >= 1 && x <= 3; });

        switch (choice) {
        case 1:
            showRegistrationScreen();
        case 2:
            showLoginScreen();
            break;
        case 3:
            return;
        }
    }
}

void showRegistrationScreen() {
    printHeader("РЕГИСТРАЦИЯ");

    Employee newEmployee;
    newEmployee.input();

    employees.push_back(new Employee(newEmployee));
    saveEmployees();

    cout << "Регистрация успешна! Теперь войдите в систему." << endl;
    system("pause");
}

void showLoginScreen() {
    printHeader("АВТОРИЗАЦИЯ");

    string login, password;

    cout << "Логин: ";
    getline(cin, login);
    cout << "Пароль: ";
    getline(cin, password);

    Employee* user = loginUser(login, password);

    if (user) {
        cout << "Вход выполнен успешно!" << endl;
        system("pause");

        if (user->getRole() == "admin") {
            showAdminMenu(user);
        }
        else if (user->getRole() == "manager") {
            showManagerMenu(user);
        }
    }
    else {
        cout << "Ошибка входа! Неверный логин или пароль." << endl;
        system("pause");
    }
}

// АДМИНИСТРАТОР

void showAdminMenu(Employee* admin) {
    while (true) {
        printHeader("МЕНЮ АДМИНИСТРАТОРА");
        cout << "Добро пожаловать, " << admin->getFirstName() << " " << admin->getLastName() << "!" << endl << endl;

        cout << "1. Управление товарами" << endl;
        cout << "2. Управление менеджерами" << endl;
        cout << "3. Просмотр транзакций" << endl;
        cout << "4. Выйти из аккаунта" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор",
            [](int x) { return x >= 1 && x <= 4; });

        switch (choice) {
        case 1:
            showAdminProductsMenu();
            break;
        case 2:
            showAdminManagersMenu();
            break;
        case 3:
            printHeader("ТРАНЗАКЦИИ");
            printTransactionsTable();
            system("pause");
            break;
        case 4:
            return;
        }
    }
}

void showAdminProductsMenu() {
    vector<Product*> currentProducts = products;

    while (true) {
        printHeader("УПРАВЛЕНИЕ ТОВАРАМИ");
        printProductsTable(currentProducts, true, true);

        cout << "1. Добавить товар" << endl;
        cout << "2. Удалить товар" << endl;
        cout << "3. Изменить статус товара (в наличии/продано)" << endl;
        cout << "4. Сортировать (категория)" << endl;
        cout << "5. Сортировать (цена по убыванию)" << endl;
        cout << "6. Фильтр (В наличии)" << endl;
        cout << "7. Фильтр (Продано)" << endl;
        cout << "8. Сбросить фильтр/сортировку" << endl;
        cout << "9. Назад" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор",
            [](int x) { return x >= 1 && x <= 9; });

        switch (choice) {
        case 1: {
            Product newProduct;
            newProduct.input();
            products.push_back(new Product(newProduct));
            currentProducts = products;
            saveProducts();
            break;
        }
        case 2: {
            if (currentProducts.empty()) {
                cout << "Нет товаров для удаления!" << endl;
                system("pause");
                break;
            }
            int id = chek<int>("Введите ID товара для удаления", "Неверный ID",
                [](int x) { return x > 0; });
            bool found = false;
            for (auto it = products.begin(); it != products.end(); ++it) {
                if ((*it)->getId() == id) {
                    if (danetka("Вы уверены что хотите удалить этот товар?")) {
                        delete* it;
                        products.erase(it);
                        currentProducts = products;
                        saveProducts();
                        cout << "Товар удален!" << endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Товар не найден!" << endl;
            system("pause");
            break;
        }
        case 3: {
            if (currentProducts.empty()) {
                cout << "Нет товаров!" << endl;
                system("pause");
                break;
            }
            int id = chek<int>("Введите ID товара", "Неверный ID",
                [](int x) { return x > 0; });
            bool found = false;
            for (auto product : products) {
                if (product->getId() == id) {
                    if (product->getStatus()) {
                        if (danetka("Товар в наличии. Изменить статус на 'Продано'?")) {
                            product->setStatus(false);
                            currentProducts = products;
                            saveProducts();
                            cout << "Статус товара изменен на 'Продано'!" << endl;
                        }
                    }
                    else {
                        if (danetka("Товар продан. Изменить статус на 'В наличии'?")) {
                            product->setStatus(true);
                            currentProducts = products;
                            saveProducts();
                            cout << "Статус товара изменен на 'В наличии'!" << endl;
                        }
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Товар не найден!" << endl;
            system("pause");
            break;
        }
        case 4:
            sortProductsByCategory(currentProducts);
            break;
        case 5:
            sortProductsByPrice(currentProducts);
            break;
        case 6:
            currentProducts = filterProducts(products, 1);
            break;
        case 7:
            currentProducts = filterProducts(products, 2);
            break;
        case 8:
            currentProducts = products;
            break;
        case 9:
            return;
        }
    }
}

void showAdminManagersMenu() {
    vector<Employee*> currentEmployees = employees;

    while (true) {
        printHeader("УПРАВЛЕНИЕ МЕНЕДЖЕРАМИ");
        printEmployeesTable(currentEmployees, true, true);

        cout << "1. Добавить менеджера" << endl;
        cout << "2. Уволить/восстановить менеджера" << endl;
        cout << "3. Сортировать (фамилия, имя)" << endl;
        cout << "4. Фильтр (Работающие)" << endl;
        cout << "5. Фильтр (Уволенные)" << endl;
        cout << "6. Сбросить фильтр/сортировку" << endl;
        cout << "7. Назад" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор",
            [](int x) { return x >= 1 && x <= 7; });

        switch (choice) {
        case 1: {
            Employee newEmployee;
            newEmployee.input();
            employees.push_back(new Employee(newEmployee));
            currentEmployees = employees;
            saveEmployees();
            break;
        }
        case 2: {
            if (employees.size() <= 1) {
                cout << "Нельзя уволить последнего сотрудника!" << endl;
                system("pause");
                break;
            }
            int id = chek<int>("Введите ID менеджера", "Неверный ID",
                [](int x) { return x > 0; });
            bool found = false;
            for (auto employee : employees) {
                if (employee->getEmployeeId() == id && employee->getRole() == "manager") {
                    if (employee->getIsActive()) {
                        if (danetka("Вы уверены что хотите уволить этого менеджера?")) {
                            employee->setIsActive(false);
                            currentEmployees = employees;
                            saveEmployees();
                            cout << "Менеджер уволен!" << endl;
                        }
                    }
                    else {
                        if (danetka("Вы уверены что хотите восстановить этого менеджера?")) {
                            employee->setIsActive(true);
                            currentEmployees = employees;
                            saveEmployees();
                            cout << "Менеджер восстановлен!" << endl;
                        }
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Менеджер не найден!" << endl;
            system("pause");
            break;
        }
        case 3:
            sortEmployees(currentEmployees);
            break;
        case 4:
            currentEmployees = filterEmployees(employees, 1);
            break;
        case 5:
            currentEmployees = filterEmployees(employees, 2);
            break;
        case 6:
            currentEmployees = employees;
            break;
        case 7:
            return;
        }
    }
}

// МЕНЕДЖЕР

void showManagerMenu(Employee* manager) {
    while (true) {
        printHeader("МЕНЮ МЕНЕДЖЕРА");
        cout << "Добро пожаловать, " << manager->getFirstName() << " " << manager->getLastName() << "!" << endl << endl;

        cout << "1. Оформить покупку" << endl;
        cout << "2. Просмотр продукции" << endl;
        cout << "3. Просмотр менеджеров" << endl;
        cout << "4. Просмотр транзакций" << endl;
        cout << "5. Выйти из аккаунта" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор",
            [](int x) { return x >= 1 && x <= 5; });

        switch (choice) {
        case 1: {
            system("cls");
            printHeader("ОФОРМЛЕНИЕ ПОКУПКИ");
            Transaction newTransaction;
            newTransaction.input(manager->getLogin());
            if (!newTransaction.getProductIds().empty()) {
                transactions.push_back(new Transaction(newTransaction));
                saveTransactions();
                saveProducts();
                cout << "Покупка оформлена!" << endl;
                system("pause");
            }
            break;
        }
        case 2:
            showManagerProductsMenu();
            break;
        case 3:
            showManagerManagersMenu();
            break;
        case 4:
            printHeader("ТРАНЗАКЦИИ");
            printTransactionsTable();
            system("pause");
            break;
        case 5:
            return;
        }
    }
}

void showManagerProductsMenu() {
    while (true) {
        printHeader("ПРОСМОТР ПРОДУКЦИИ");
        printProductsTable(products, true, false);

        cout << "1. Посмотреть подробную информацию" << endl;
        cout << "2. Назад" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор", [](int x) { return x == 1 || x == 2; });

        if (choice == 1) {
            int id = chek<int>("Введите ID товара", "Неверный ID",
                [](int x) { return x >= 0; });

            bool found = false;
            for (auto product : products) {
                if (product->getId() == id) {
                    product->printDetails();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Товар с  таким ID не найден!" << endl;
            }
            system("pause");
        }
        else {
            return;
        }
    }
}

void showManagerManagersMenu() {
    while (true) {
        printHeader("ПРОСМОТР МЕНЕДЖЕРОВ");
        vector<Employee*> workingManagers = filterEmployees(employees, 1);
        printEmployeesTable(workingManagers, true, false);

        cout << "1. Посмотреть подробную информацию" << endl;
        cout << "2. Назад" << endl;
        cout << endl;

        int choice = chek<int>("Выберите действие", "Неверный выбор",
            [](int x) { return x == 1 || x == 2; });

        if (choice == 1) {
            int id = chek<int>("Введите ID менеджера", "Неверный ID",
                [](int x) { return x >= 0; });

            bool found = false;
            for (auto employee : employees) {
                if (employee->getEmployeeId() == id && employee->getRole() == "manager" && employee->getIsActive()) {
                    employee->printDetails();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Менеджер с  таким ID не найден!" << endl;
            }
            system("pause");
        }
        else {
            return;
        }
    }
}