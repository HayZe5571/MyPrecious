#include "MyLibrary.h"

Transaction::Transaction(int id, const string& dateTime, const string& employeeLogin, const vector<int>& productIds, const vector<string>& productNames, const vector<double>& productPrices, const string& clientFullName, const string& clientPhone, double totalPrice) {
    this->id = id;
    this->dateTime = dateTime;
    this->employeeLogin = employeeLogin;
    this->productIds = productIds;
    this->productNames = productNames;
    this->productPrices = productPrices;
    this->clientFullName = clientFullName;
    this->clientPhone = clientPhone;
    this->totalPrice = totalPrice;
}

int Transaction::getId() const { return id; }
string Transaction::getDateTime() const { return dateTime; }
string Transaction::getEmployeeLogin() const { return employeeLogin; }
vector<int> Transaction::getProductIds() const { return productIds; }
vector<string> Transaction::getProductNames() const { return productNames; }
vector<double> Transaction::getProductPrices() const { return productPrices; }
string Transaction::getClientFullName() const { return clientFullName; }
string Transaction::getClientPhone() const { return clientPhone; }
double Transaction::getTotalPrice() const { return totalPrice; }

void Transaction::setId(int id) { this->id = id; }
void Transaction::setDateTime(const string& dateTime) { this->dateTime = dateTime; }
void Transaction::setEmployeeLogin(const string& employeeLogin) { this->employeeLogin = employeeLogin; }
void Transaction::setProductIds(const vector<int>& productIds) { this->productIds = productIds; }
void Transaction::setProductNames(const vector<string>& productNames) { this->productNames = productNames; }
void Transaction::setProductPrices(const vector<double>& productPrices) { this->productPrices = productPrices; }
void Transaction::setClientFullName(const string& clientFullName) { this->clientFullName = clientFullName; }
void Transaction::setClientPhone(const string& clientPhone) { this->clientPhone = clientPhone; }
void Transaction::setTotalPrice(double totalPrice) { this->totalPrice = totalPrice; }

bool Transaction::validateClientPhone(const string& phone) const {
    if (phone.length() != 13) return false;
    if (phone.substr(0, 4) != "+375") return false;
    return all_of(phone.begin() + 4, phone.end(), ::isdigit);
}

string Transaction::inputClientPhone() const {
    string phone;
    while (true) {
        cout << "Телефон клиента (+375XXXXXXXXX): ";
        getline(cin, phone);
        if (validateClientPhone(phone)) return phone;
        cout << "Ошибка: формат +375 и 9 цифр (всего 13 символов)" << endl;
    }
}

void Transaction::input(const string& currentEmployeeLogin) {
    employeeLogin = currentEmployeeLogin;
    dateTime = getCurrentDateTime();
    id = generateUniqueId();

    cout << "Выберите товары для продажи:\n";

    vector<Product*> availableProducts;
    for (auto product : products) {
        if (product->getStatus()) {
            availableProducts.push_back(product);
        }
    }

    if (availableProducts.empty()) {
        cout << "Нет товаров в наличии!\n";
        return;
    }

    int counter = 1;
    for (auto product : availableProducts) {
        cout << setw(3) << left << counter++ << " | ";
        cout << "ID: " << setw(7) << product->getId()
            << " | Название: " << setw(30) << left
            << (product->getName().length() > 28 ? product->getName().substr(0, 25) + "..." : product->getName())
            << " | Цена: " << fixed << setprecision(2)
            << setw(10) << product->getPrice() << " руб.\n";
    }

    cout << "\nВведите номера товаров через запятую: ";
    string selection;
    getline(cin, selection);

    vector<string> strNumbers = splitString(selection, ',');
    totalPrice = 0.0;
    vector<int> selectedIndices;

    for (const auto& strNum : strNumbers) {
        try {
            int choice = stoi(strNum);
            if (choice >= 1 && choice <= availableProducts.size()) {
                if (find(selectedIndices.begin(), selectedIndices.end(), choice - 1) != selectedIndices.end()) {
                    cout << "Товар №" << choice << " уже выбран!\n";
                    continue;
                }

                Product* selectedProduct = availableProducts[choice - 1];
                productIds.push_back(selectedProduct->getId());
                productNames.push_back(selectedProduct->getName());
                productPrices.push_back(selectedProduct->getPrice());
                totalPrice += selectedProduct->getPrice();
                selectedProduct->setStatus(false);
                selectedIndices.push_back(choice - 1);
            }
        }
        catch (...) {
            continue;
        }
    }

    if (productIds.empty()) {
        cout << "Не выбран ни один товар!\n";
        return;
    }

    cout << "\nДанные клиента:\n";

    while (true) {
        cout << "ФИО клиента: ";
        getline(cin, clientFullName);

        if (isValidName(clientFullName)) {
            break;
        }
        else {
            cout << "ФИО должно содержать только буквы, пробелы, дефисы, точки и апострофы!\n";
        }
    }

    clientPhone = inputClientPhone();
}

void Transaction::printTable() const {
    if (id == 0) return;

    cout << setw(7) << left << id
        << setw(20) << left << dateTime
        << setw(12) << left << employeeLogin
        << setw(20) << left << (clientFullName.length() > 18 ? clientFullName.substr(0, 15) + "..." : clientFullName)
        << setw(15) << left << clientPhone
        << setw(10) << left << fixed << setprecision(2) << totalPrice << endl;

    for (size_t i = 0; i < productIds.size(); i++) {
        cout << setw(7) << left << ""
            << setw(20) << left << ""
            << setw(12) << left << ""
            << setw(7) << left << productIds[i]
            << setw(33) << left << (productNames[i].length() > 30 ? productNames[i].substr(0, 27) + "..." : productNames[i])
            << setw(10) << left << fixed << setprecision(2) << productPrices[i] << endl;
    }
}

void Transaction::saveToFile(ofstream& file) const {
    file << id << ";" << dateTime << ";" << employeeLogin << ";"
        << joinString(productIds, '|') << ";"
        << joinString(productNames, '|') << ";"
        << joinString(productPrices, '|') << ";"
        << clientFullName << ";" << clientPhone << ";"
        << fixed << setprecision(2) << totalPrice << endl;
}

void Transaction::loadFromFile(const vector<string>& fields) {
    if (fields.size() < 9) {
        cout << "Транзакция с ID " << (fields.size() > 0 ? fields[0] : "неизвестно")
            << " не загружена (неверное количество полей: " << fields.size() << ")\n";
        return;
    }

    id = stoi(fields[0]);
    dateTime = fields[1];
    employeeLogin = fields[2];

    vector<string> idStrings = splitString(fields[3], '|');
    for (const auto& idStr : idStrings) {
        productIds.push_back(stoi(idStr));
    }

    productNames = splitString(fields[4], '|');

    vector<string> priceStrings = splitString(fields[5], '|');
    for (const auto& priceStr : priceStrings) {
        productPrices.push_back(stod(priceStr));
    }

    clientFullName = fields[6];
    clientPhone = fields[7];
    totalPrice = stod(fields[8]);
}