# 🏦 Bank Management System — C++

> A complete client management system built in C++ using text files for persistent storage.

---

## 📌 Project Overview

This program stores client data in a text file (`DataBaseBank`) and allows full client management through a structured main menu and transactions sub-menu.

---

## ✅ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Show Clients** | Displays all clients in a formatted table |
| 2 | **Add Client** | Adds a new client with duplicate account number check |
| 3 | **Delete Client** | Soft-deletes a client with confirmation |
| 4 | **Update Client** | Edits an existing client's data |
| 5 | **Find Client** | Searches for a client by account number |
| 6 | **Transactions** | Opens a sub-menu for financial operations |
| → | **Deposit** | Adds amount to client balance |
| → | **Withdraw** | Deducts amount with insufficient balance check |
| → | **Total Balances** | Shows all balances and the total sum |

---

## 🧠 How Data Flows

```
Text File (DataBaseBank)
    ↓ vloaddatainfile()
vector<sclient>  ← each element is a full struct
    ↓ search / delete / update / deposit / withdraw
    ↓ DeletDataAndSaveAgain()
Text File (updated)
```

---

## 🗂️ Code Structure

```
sclient (struct)
├── acount_number
├── pincode
├── name
├── phone
├── acount_balance
└── markof_delet       ← used for soft delete

Shared Functions:
├── vloaddatainfile()             ← load file into vector
├── convertLineToStrust()         ← line → struct
├── convertDataToLine()           ← struct → line
├── vsplitstring()                ← split line by delimiter
├── check_acountnumberistrue()    ← search (shared across all ops)
├── addDataLineToFile()           ← append new record to file
└── DeletDataAndSaveAgain()       ← rewrite entire file from vector

Main Menu Operations:
├── [1] ShowClient()
├── [2] addnewclient()     ← read_out() + MadeOpearteAdd()
├── [3] delet()            ← markdeletclient() + DeletDataAndSaveAgain()
├── [4] updata_data()      ← ChangeClientRecord()
├── [5] search()
└── [6] TransactionsMenu() ← sub-menu below

Transactions Sub-Menu:
├── [1] depost()           ← deposit to account
├── [2] withdraw()         ← withdraw with balance check
└── [3] ShowTotalBalances() ← calcTotalBalances()
```

---

## 💡 Key Concepts Used

**Soft Delete**
Instead of removing directly from the vector, we mark the client with `markof_delet = true` and skip it when rewriting the file. This keeps the logic clean and safe.

**Forward Declarations**
Allows functions to reference each other regardless of order in the file:
```cpp
sclient convertLineToStrust(string line, string delim = "#//#");
bool check_acountnumberistrue(string acountnumber, vector<sclient>& vclient, sclient& client);
double calcTotalBalances(vector<sclient> vclient);
```

**Custom Delimiter**
`#//#` separates each client's fields in a line so they can be split again using `vsplitstring()`.

**Duplicate Account Check**
When adding a new client, the program loops until a unique account number is entered:
```cpp
while (check_acountnumberistrue(client.acount_number, vclient, temp)) {
    cout << "Number already exists, Enter another? ";
    getline(cin, client.acount_number);
}
```

**Transactions Sub-Menu**
Deposit and Withdraw update the balance directly in the vector, then immediately rewrite the file using `DeletDataAndSaveAgain()`.

---

## 🚀 How to Run

1. Open `teast progect bank.sln` in **Visual Studio**
2. Press `Ctrl + F5` to build and run
3. Follow the main menu

---

## 📁 Files

| File | Description |
|------|-------------|
| `teast progect bank.cpp` | Main source code |
| `DataBaseBank` | Text-based database (auto-created) |
| `README.md` | Project documentation |
| `index.html` | Interactive code map — open in browser |

---

## 🗺️ Interactive Code Map

👉 **[Open Interactive Code Map](https://ahmedtamerahmed692-maker.github.io/teast-progect-bank/index.html)**

Click the link above to explore all functions and their relationships visually in your browser — no download needed!

---

## 👨‍💻 Developer

**Ahmed Tamer** — Educational project for learning C++ and file management.
