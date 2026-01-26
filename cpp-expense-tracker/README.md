# Expense Tracker (C++ Console) 💰

A **menu-driven C++ console application** to track daily expenses.
Built to practice **OOP, file handling, and clean project structure**.

## ✨ Features
- Add expense (date, category, amount, note)
- List all expenses
- Filter by category
- Monthly summary (total + by category)
- Data persistence using **CSV file** (`data/expenses.csv`)
- Simple input validation

## 🧰 Tech Stack
- C++17 (standard library only)

## ▶️ Build & Run

### Linux / macOS
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/ExpenseStore.cpp src/Utils.cpp -o tracker
./tracker
```

### Windows (MinGW)
```bash
g++ -std=c++17 -Iinclude src\main.cpp src\ExpenseStore.cpp src\Utils.cpp -o tracker.exe
tracker.exe
```

## 👤 Author
Fardin Mustafi
