#include "ExpenseStore.h"
#include "Utils.h"
#include <fstream>

ExpenseStore::ExpenseStore(std::string csv_path) : path_(std::move(csv_path)) {}

bool ExpenseStore::load() {
    items_.clear();
    std::ifstream in(path_);
    if (!in.is_open()) return true; // no file yet is ok

    std::string line;
    bool first = true;
    while (std::getline(in, line)) {
        if (first) { first = false; continue; } // header
        if (utils::trim(line).empty()) continue;

        auto fields = utils::split_csv_line(line);
        if (fields.size() < 4) continue;

        Expense e;
        e.date = fields[0];
        e.category = fields[1];

        double amt = 0.0;
        if (!utils::to_double(fields[2], amt)) continue;
        e.amount = amt;

        e.note = fields[3];
        items_.push_back(e);
    }
    return true;
}

bool ExpenseStore::save() const {
    std::ofstream out(path_, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "date,category,amount,note\n";
    for (const auto& e : items_) {
        out << utils::escape_csv(e.date) << ","
            << utils::escape_csv(e.category) << ","
            << e.amount << ","
            << utils::escape_csv(e.note) << "\n";
    }
    return true;
}

void ExpenseStore::add(const Expense& e) { items_.push_back(e); }
const std::vector<Expense>& ExpenseStore::all() const { return items_; }

std::vector<Expense> ExpenseStore::filter_by_category(const std::string& category) const {
    std::vector<Expense> res;
    for (const auto& e : items_) if (e.category == category) res.push_back(e);
    return res;
}

ExpenseStore::Summary ExpenseStore::monthly_summary(int year, int month) const {
    Summary s;
    for (const auto& e : items_) {
        if (e.date.size() < 10) continue;
        int y = std::stoi(e.date.substr(0,4));
        int m = std::stoi(e.date.substr(5,2));
        if (y == year && m == month) {
            s.total += e.amount;
            s.by_category[e.category] += e.amount;
        }
    }
    return s;
}
