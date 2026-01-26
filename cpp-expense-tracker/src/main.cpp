#include "ExpenseStore.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

static void print_menu() {
    std::cout << "\n=== Expense Tracker (C++) ===\n"
              << "1) Add expense\n"
              << "2) List all expenses\n"
              << "3) Filter by category\n"
              << "4) Monthly summary\n"
              << "5) Save\n"
              << "6) Exit\n"
              << "Choose: ";
}

static void list_expenses(const std::vector<Expense>& items) {
    if (items.empty()) { std::cout << "No expenses found.\n"; return; }
    std::cout << "\nDate        | Category       | Amount   | Note\n";
    std::cout << "------------+----------------+----------+-------------------------\n";
    for (const auto& e : items) {
        std::cout << std::left << std::setw(11) << e.date << " | "
                  << std::setw(14) << e.category << " | "
                  << std::right << std::setw(8) << std::fixed << std::setprecision(2) << e.amount << " | "
                  << e.note << "\n";
    }
}

static std::string read_line(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return utils::trim(s);
}

int main() {
    ExpenseStore store("data/expenses.csv");
    store.load();

    while (true) {
        print_menu();
        std::string choice;
        std::getline(std::cin, choice);
        choice = utils::trim(choice);

        if (choice == "1") {
            Expense e;
            e.date = read_line("Date (YYYY-MM-DD): ");
            if (!utils::is_valid_date(e.date)) { std::cout << "Invalid date.\n"; continue; }

            e.category = read_line("Category (e.g., Food): ");
            if (e.category.empty()) { std::cout << "Category cannot be empty.\n"; continue; }

            std::string amt_s = read_line("Amount: ");
            double amt = 0.0;
            if (!utils::to_double(amt_s, amt) || amt <= 0) { std::cout << "Invalid amount.\n"; continue; }
            e.amount = amt;

            e.note = read_line("Note (optional): ");
            store.add(e);
            std::cout << "✅ Added.\n";

        } else if (choice == "2") {
            list_expenses(store.all());

        } else if (choice == "3") {
            std::string cat = read_line("Category: ");
            list_expenses(store.filter_by_category(cat));

        } else if (choice == "4") {
            std::string y_s = read_line("Year (e.g., 2026): ");
            std::string m_s = read_line("Month (1-12): ");
            int y = 0, m = 0;
            try { y = std::stoi(y_s); m = std::stoi(m_s); }
            catch (...) { std::cout << "Invalid year/month.\n"; continue; }
            if (m < 1 || m > 12) { std::cout << "Month must be 1-12.\n"; continue; }

            auto s = store.monthly_summary(y, m);
            std::cout << "\nSummary for " << y << "-" << std::setw(2) << std::setfill('0') << m << std::setfill(' ') << "\n";
            std::cout << "Total: " << std::fixed << std::setprecision(2) << s.total << "\n";
            std::cout << "By category:\n";
            for (const auto& kv : s.by_category) {
                std::cout << " - " << kv.first << ": " << std::fixed << std::setprecision(2) << kv.second << "\n";
            }

        } else if (choice == "5") {
            std::cout << (store.save() ? "✅ Saved.\n" : "❌ Save failed.\n");

        } else if (choice == "6") {
            store.save(); // auto-save on exit
            std::cout << "Bye!\n";
            break;

        } else {
            std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}
