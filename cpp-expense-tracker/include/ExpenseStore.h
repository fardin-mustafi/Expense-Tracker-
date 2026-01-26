#pragma once
#include "Expense.h"
#include <string>
#include <vector>
#include <map>

class ExpenseStore {
public:
    explicit ExpenseStore(std::string csv_path);

    bool load();
    bool save() const;

    void add(const Expense& e);
    const std::vector<Expense>& all() const;

    std::vector<Expense> filter_by_category(const std::string& category) const;

    struct Summary {
        double total = 0.0;
        std::map<std::string, double> by_category;
    };

    Summary monthly_summary(int year, int month) const;

private:
    std::string path_;
    std::vector<Expense> items_;
};
