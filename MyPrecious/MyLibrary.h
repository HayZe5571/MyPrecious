#pragma once

#define NOMINMAX

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <concepts>
#include <functional>
#include <random>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <locale>
#include <map>
#include <windows.h>

using namespace std;

class Employee;
class Product;
class Transaction;

#include "Source.h"
#include "Password.h"

#include "Employee.h"
#include "Product.h"
#include "Transaction.h"

#include "Authorization.h"
#include "File.h"
#include "Table.h"
#include "ScreenMenu.h"

extern vector<Employee*> employees;
extern vector<Product*> products;
extern vector<Transaction*> transactions;

extern const string EMPLOYEES_FILE;
extern const string PRODUCTS_FILE;
extern const string TRANSACTIONS_FILE;