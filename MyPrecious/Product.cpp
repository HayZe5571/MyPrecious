#include "MyLibrary.h"

Product::Product(int id, const string& name, const string& category, const vector<string>& materials, const vector<string>& stoneTypes, double price, bool status) {
    this->id = id;
    this->name = name;
    this->category = category;
    this->materials = materials;
    this->stoneTypes = stoneTypes;
    this->price = price;
    this->status = status;
}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
string Product::getCategory() const { return category; }
vector<string> Product::getMaterials() const { return materials; }
vector<string> Product::getStoneTypes() const { return stoneTypes; }
double Product::getPrice() const { return price; }
bool Product::getStatus() const { return status; }

void Product::setId(int id) { this->id = id; }
void Product::setName(const string& name) { this->name = name; }
void Product::setCategory(const string& category) { this->category = category; }
void Product::setMaterials(const vector<string>& materials) { this->materials = materials; }
void Product::setStoneTypes(const vector<string>& stoneTypes) { this->stoneTypes = stoneTypes; }
void Product::setPrice(double price) { this->price = price; }
void Product::setStatus(bool status) { this->status = status; }

void Product::restock() {
    status = true;
}

void Product::input() {
    cout << "Название: ";
    getline(cin, name);

    vector<string> categories = { "Часы", "Кольца", "Серьги", "Цепи", "Браслеты", "Подвески", "Кулоны", "Запонки", "Броши", "Колье" };
    category = chooseFromList(categories, "Выберите категорию");

    vector<string> materialsList = { "Золото жёлтое", "Золото белое", "Золото розовое", "Серебро", "Платина", "Сталь хирургическая", "Кожа", "Титан" };
    vector<int> materialChoices = chooseMultipleFromList(materialsList, "Выберите материалы (1-2)");

    while (materialChoices.size() > 2) {
        cout << "Можно выбрать не более 2 материалов!\n";
        materialChoices = chooseMultipleFromList(materialsList, "Выберите материалы (1-2)");
    }

    materials.clear();
    for (int choice : materialChoices) {
        materials.push_back(materialsList[choice]);
    }

    vector<string> stoneTypesList = { "Бриллиант", "Сапфир", "Рубин", "Изумруд", "Жемчуг", "Топаз", "Аметист", "Опал", "Гранат", "нет" };
    vector<int> stoneChoices;

    bool canHaveStones = false;
    for (const string& material : materials) {
        if (material != "Кожа" && material != "Титан" && material != "Сталь хирургическая") {
            canHaveStones = true;
            break;
        }
    }

    if (!canHaveStones) {
        stoneTypes.push_back("нет");
        cout << "Для выбранных материалов камни недоступны. Установлено: нет\n";
    }
    else {
        stoneChoices = chooseMultipleFromList(stoneTypesList, "Выберите типы камней (1-2) или 'нет'");

        while (stoneChoices.size() > 2) {
            cout << "Можно выбрать не более 2 камней!\n";
            stoneChoices = chooseMultipleFromList(stoneTypesList, "Выберите типы камней (1-2) или 'нет'");
        }

        stoneTypes.clear();
        for (int choice : stoneChoices) {
            stoneTypes.push_back(stoneTypesList[choice]);
        }

        if (stoneTypes.size() == 2) {
            if (stoneTypes[0] == "нет" || stoneTypes[1] == "нет") {
                stoneTypes.clear();
                stoneTypes.push_back("нет");
            }
        }

        if (stoneTypes.size() == 1 && stoneTypes[0] == "нет") {
            stoneTypes.clear();
            stoneTypes.push_back("нет");
        }
    }

    price = chek<double>("Цена", "Неверная цена", [](double x) { return x > 0 && x <= 999999.99; });
    status = true;
    id = generateUniqueId();
}

void Product::printTable(bool showId, bool showStatus) const {
    if (id == 0) return;

    string displayName = name;
    if (displayName.length() > 35) displayName = displayName.substr(0, 32) + "...";

    string displayMaterials = joinString(materials, ',');
    if (displayMaterials.length() > 20) displayMaterials = displayMaterials.substr(0, 17) + "...";

    string displayStones = joinString(stoneTypes, ',');
    if (displayStones.length() > 15) displayStones = displayStones.substr(0, 12) + "...";

    if (showId) {
        cout << setw(7) << left << id;
    }

    cout << setw(36) << left << displayName
        << setw(10) << left << category
        << setw(21) << left << displayMaterials
        << setw(16) << left << displayStones
        << setw(10) << left << fixed << setprecision(2) << price;

    if (showStatus) {
        if (status) {
            cout << "\033[32m" << setw(10) << left << "В наличии" << "\033[0m";
        }
        else {
            cout << "\033[91m" << setw(10) << left << "Продано" << "\033[0m";
        }
    }

    cout << endl;
}

void Product::printDetails() const {
    if (id == 0) return;

    cout << "ID товара: " << id << endl;
    cout << "Название: " << name << endl;
    cout << "Категория: " << category << endl;
    cout << "Материалы: " << joinString(materials, ',') << endl;
    cout << "Типы камней: " << joinString(stoneTypes, ',') << endl;
    cout << "Цена: " << fixed << setprecision(2) << price << " руб." << endl;
    cout << "Статус: " << (status ? "В наличии" : "Продано") << endl;
}

void Product::saveToFile(ofstream& file) const {
    file << id << ";" << name << ";" << category << ";"
        << joinString(materials, '|') << ";"
        << joinString(stoneTypes, '|') << ";"
        << fixed << setprecision(2) << price << ";" << status << endl;
}

void Product::loadFromFile(const vector<string>& fields) {
    if (fields.size() < 7) {
        cout << "Товар с ID " << (fields.size() > 0 ? fields[0] : "неизвестно")
            << " не загружен (неверное количество полей: " << fields.size() << ")\n";
        return;
    }

    id = stoi(fields[0]);
    name = fields[1];
    category = fields[2];
    materials = splitString(fields[3], '|');
    stoneTypes = splitString(fields[4], '|');
    price = stod(fields[5]);
    status = stoi(fields[6]);
}