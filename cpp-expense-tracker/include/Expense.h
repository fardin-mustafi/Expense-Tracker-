#pragma once
#include <string>

struct Expense {
    std::string date;      // YYYY-MM-DD
    std::string category;  // e.g., Food, Transport
    double amount = 0.0;
    std::string note;
};
