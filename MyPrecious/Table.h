#pragma once

#include <vector>
#include <string>

using namespace std;

class Employee;
class Product;

extern void printEmployeesTable(bool showId, bool showIsActive);
extern void printProductsTable(bool showId, bool showStatus);
extern void printTransactionsTable();

extern void printEmployeesTable(const vector<Employee*>& empList, bool showId, bool showIsActive);
extern void printProductsTable(const vector<Product*>& prodList, bool showId, bool showStatus);

extern vector<Employee*> filterEmployees(const vector<Employee*>& source, int filterType);
extern vector<Product*> filterProducts(const vector<Product*>& source, int filterType);

extern void sortEmployees(vector<Employee*>& empList);
extern void sortProductsByCategory(vector<Product*>& prodList);
extern void sortProductsByPrice(vector<Product*>& prodList);