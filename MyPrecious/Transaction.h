#pragma once

class Transaction {
private:
    int id = 0;
    string dateTime;
    string employeeLogin;
    vector<int> productIds;
    vector<string> productNames;
    vector<double> productPrices;
    string clientFullName;
    string clientPhone;
    double totalPrice = 0.0;

    bool validateClientPhone(const string& phone) const;
    string inputClientPhone() const;

public:
    Transaction() = default;
    Transaction(int id, const string& dateTime, const string& employeeLogin, const vector<int>& productIds, const vector<string>& productNames, const vector<double>& productPrices, const string& clientFullName, const string& clientPhone, double totalPrice);
    Transaction(const Transaction& other) = default;
    ~Transaction() = default;

    int getId() const;
    string getDateTime() const;
    string getEmployeeLogin() const;
    vector<int> getProductIds() const;
    vector<string> getProductNames() const;
    vector<double> getProductPrices() const;
    string getClientFullName() const;
    string getClientPhone() const;
    double getTotalPrice() const;

    void setId(int id);
    void setDateTime(const string& dateTime);
    void setEmployeeLogin(const string& employeeLogin);
    void setProductIds(const vector<int>& productIds);
    void setProductNames(const vector<string>& productNames);
    void setProductPrices(const vector<double>& productPrices);
    void setClientFullName(const string& clientFullName);
    void setClientPhone(const string& clientPhone);
    void setTotalPrice(double totalPrice);

    void input(const string& currentEmployeeLogin);
    void printTable() const;
    void saveToFile(ofstream& file) const;
    void loadFromFile(const vector<string>& fields);
};