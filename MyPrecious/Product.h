#pragma once

class Product {
private:
    int id = 0;
    string name;
    string category;
    vector<string> materials;
    vector<string> stoneTypes;
    double price = 0.0;
    bool status = true;

public:
    Product() = default;
    Product(int id, const string& name, const string& category, const vector<string>& materials, const vector<string>& stoneTypes, double price, bool status);
    Product(const Product& other) = default;
    ~Product() = default;

    int getId() const;
    string getName() const;
    string getCategory() const;
    vector<string> getMaterials() const;
    vector<string> getStoneTypes() const;
    double getPrice() const;
    bool getStatus() const;

    void setId(int id);
    void setName(const string& name);
    void setCategory(const string& category);
    void setMaterials(const vector<string>& materials);
    void setStoneTypes(const vector<string>& stoneTypes);
    void setPrice(double price);
    void setStatus(bool status);

    void restock();

    void input();
    void printTable(bool showId = false, bool showStatus = false) const;
    void printDetails() const;
    void saveToFile(ofstream& file) const;
    void loadFromFile(const vector<string>& fields);
};