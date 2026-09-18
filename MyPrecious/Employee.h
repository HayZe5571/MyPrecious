#pragma once

class Employee {
private:
    string login;
    string passwordHash;
    string firstName;
    string lastName;
    string role = "manager";
    int employeeId = 0;
    bool isActive = true;

public:
    Employee() = default;
    Employee(const string& login, const string& passwordHash, const string& firstName, const string& lastName, const string& role, int employeeId, bool isActive);
    Employee(const Employee& other) = default;
    ~Employee() = default;

    string getLogin() const;
    string getPasswordHash() const;
    string getFirstName() const;
    string getLastName() const;
    string getRole() const;
    int getEmployeeId() const;
    bool getIsActive() const;

    void setLogin(const string& login);
    void setPasswordHash(const string& passwordHash);
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setRole(const string& role);
    void setEmployeeId(int employeeId);
    void setIsActive(bool isActive);

    void input();
    void printTable(bool showId = false, bool showIsActive = false) const;
    void printDetails() const;
    void saveToFile(ofstream& file) const;
    void loadFromFile(const vector<string>& fields);
};