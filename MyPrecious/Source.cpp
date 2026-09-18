#include "MyLibrary.h"

bool isValidName(const string& str) {
    if (str.empty()) return false;

    for (char c : str) {
        if (!((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= 'А' && c <= 'я') ||
            (c == 'Ё' || c == 'ё') ||
            (c == ' ') || (c == '-') ||
            (c == '.') || (c == '\''))) {
            return false;
        }
    }
    return true;
}

bool validatePhone(const string& phone) {
    if (phone.length() != 13) return false;
    if (phone.substr(0, 4) != "+375") return false;
    return all_of(phone.begin() + 4, phone.end(), ::isdigit);
}

string inputPhone(const string& prompt) {
    string phone;
    while (true) {
        cout << prompt << " (+375XXXXXXXXX): ";
        getline(cin, phone);
        if (validatePhone(phone)) {
            return phone;
        }
        cout << "Ошибка: формат +375 и 9 цифр (всего 13 символов)" << endl;
    }
}

int generateUniqueId() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100000, 999999);

    auto idExists = [](int id) {
        for (auto e : employees) if (e->getEmployeeId() == id) return true;
        for (auto p : products) if (p->getId() == id) return true;
        for (auto t : transactions) if (t->getId() == id) return true;
        return false;
        };

    int newId;
    do {
        newId = dist(gen);
    } while (idExists(newId));

    return newId;
}

string getCurrentDateTime() {
    time_t now = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M", &localTime);
    return string(buffer);
}

string toLower(const string& str) {
    string result = str;
    for (char& c : result) c = tolower(c);
    return result;
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);
        result.push_back(item);
    }
    return result;
}

template<typename T>
string joinString(const vector<T>& vec, char delimiter) {
    if (vec.empty()) return "";
    stringstream ss;
    ss << vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        ss << delimiter << vec[i];
    }
    return ss.str();
}

template string joinString<int>(const vector<int>&, char);
template string joinString<double>(const vector<double>&, char);
template string joinString<string>(const vector<string>&, char);

bool danetka(const string& prompt) {
    cout << prompt + ": ";

    string answer;
    while (true) {
        getline(cin, answer);
        answer = toLower(answer);

        if (answer == "да" || answer == "д" || answer == "1") return true;
        if (answer == "нет" || answer == "н" || answer == "0") return false;

        cout << "Пожалуйста, введите 'да' или 'нет': ";
    }
}

string chooseFromList(const vector<string>& options, const string& prompt) {
    cout << prompt << ":\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }

    int choice;
    while (true) {
        cout << "Выберите номер: ";
        cin >> choice;
        if (cin.good() && choice >= 1 && choice <= static_cast<int>(options.size())) {
            cin.ignore();
            return options[choice - 1];
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный номер! ";
    }
}

vector<int> chooseMultipleFromList(const vector<string>& options, const string& prompt) {
    cout << prompt << ":\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }

    cout << "Введите номера через запятую: ";
    string input;
    getline(cin, input);

    vector<string> strNumbers = splitString(input, ',');
    vector<int> choices;

    for (const auto& str : strNumbers) {
        try {
            int num = stoi(str);
            if (num >= 1 && num <= static_cast<int>(options.size())) {
                choices.push_back(num - 1);
            }
        }
        catch (...) {
            continue;
        }
    }
    return choices;
}

template<typename T>
T chek(const string& prompt, const string& error, function<bool(T)> customCheck) {
    cout << prompt + ": ";
    cout << "\033[s";

    T n;
    while (!(cin >> n) || !customCheck(n)) {
        cout << "\033[u" << "\033[0J" << error + "! Введите ещё раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return n;
}

template int chek<int>(const string& prompt, const string& error, function<bool(int)> customCheck);
template double chek<double>(const string& prompt, const string& error, function<bool(double)> customCheck);