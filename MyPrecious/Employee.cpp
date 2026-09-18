#include "MyLibrary.h"

Employee::Employee(const string& login, const string& passwordHash, const string& firstName, const string& lastName, const string& role, int employeeId, bool isActive) {
    this->login = login;
    this->passwordHash = passwordHash;
    this->firstName = firstName;
    this->lastName = lastName;
    this->role = role;
    this->employeeId = employeeId;
    this->isActive = isActive;
}

string Employee::getLogin() const { return login; }
string Employee::getPasswordHash() const { return passwordHash; }
string Employee::getFirstName() const { return firstName; }
string Employee::getLastName() const { return lastName; }
string Employee::getRole() const { return role; }
int Employee::getEmployeeId() const { return employeeId; }
bool Employee::getIsActive() const { return isActive; }

void Employee::setLogin(const string& login) { this->login = login; }
void Employee::setPasswordHash(const string& passwordHash) { this->passwordHash = passwordHash; }
void Employee::setFirstName(const string& firstName) { this->firstName = firstName; }
void Employee::setLastName(const string& lastName) { this->lastName = lastName; }
void Employee::setRole(const string& role) { this->role = role; }
void Employee::setEmployeeId(int employeeId) { this->employeeId = employeeId; }
void Employee::setIsActive(bool isActive) { this->isActive = isActive; }

void Employee::input() {
    while (true) {
        cout << "Логин: ";
        getline(cin, login);

        if (login.find(' ') != string::npos) {
            cout << "Логин не должен содержать пробелов!\n";
            continue;
        }

        if (login.empty()) {
            cout << "Логин не может быть пустым!\n";
            continue;
        }

        if (!isLoginUnique(login)) {
            cout << "Логин уже занят!\n";
            continue;
        }

        break;
    }

    string password;
    while (true) {
        cout << "Пароль (мин. 4 символа): ";
        getline(cin, password);

        if (isPasswordValid(password)) {
            passwordHash = hashPassword(password);
            break;
        }
        else {
            cout << "Пароль должен содержать минимум 4 символа!\n";
        }
    }

    while (true) {
        cout << "Имя: ";
        getline(cin, firstName);

        if (!isValidName(firstName)) {
            cout << "Имя должно содержать только буквы и дефисы!\n";
            continue;
        }

        if (firstName.empty()) {
            cout << "Имя не может быть пустым!\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "Фамилия: ";
        getline(cin, lastName);

        if (!isValidName(lastName)) {
            cout << "Фамилия должна содержать только буквы и дефисы!\n";
            continue;
        }

        if (lastName.empty()) {
            cout << "Фамилия не может быть пустым!\n";
            continue;
        }

        break;
    }

    role = "manager";
    employeeId = generateUniqueId();
    isActive = true;
}

void Employee::printTable(bool showId, bool showIsActive) const {
    if (employeeId == 0) return;

    cout << setw(15) << left << login
        << setw(15) << left << firstName
        << setw(21) << left << lastName;

    if (showId) {
        cout << setw(7) << left << employeeId;
    }

    if (showIsActive) {
        if (isActive) {
            cout << "\033[32m" << setw(10) << left << "Работает" << "\033[0m";
        }
        else {
            cout << "\033[91m" << setw(10) << left << "Уволен" << "\033[0m";
        }
    }

    cout << endl;
}

void Employee::printDetails() const {
    if (employeeId == 0) return;

    cout << "Табельный номер: " << employeeId << endl;
    cout << "Логин: " << login << endl;
    cout << "Имя: " << firstName << endl;
    cout << "Фамилия: " << lastName << endl;
    cout << "Роль: " << role << endl;
    cout << "Статус: " << (isActive ? "Работает" : "Уволен") << endl;
}

void Employee::saveToFile(ofstream& file) const {
    file << login << ";" << passwordHash << ";" << firstName << ";"
        << lastName << ";" << role << ";" << employeeId << ";" << isActive << endl;
}

void Employee::loadFromFile(const vector<string>& fields) {
    if (fields.size() < 7) {
        cout << "Сотрудник с ID " << (fields.size() > 5 ? fields[5] : "неизвестно")
            << " не загружен (неверное количество полей: " << fields.size() << ")\n";
        return;
    }

    login = fields[0];
    passwordHash = fields[1];
    firstName = fields[2];
    lastName = fields[3];
    role = fields[4];
    employeeId = stoi(fields[5]);
    isActive = stoi(fields[6]);
}