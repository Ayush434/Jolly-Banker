//
// Created by ayush on 5/21/2024.
//

#include "Bank.h"
#include "Transaction.h"
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include "BSTree.h"

using namespace std;

Bank::Bank() {
    accounts = BSTree();
    transactions = queue<Transaction>();
}

void Bank::ReadTransactions(const string &filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        throw invalid_argument("File cannot be open: " + filename);
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        char type;
        int account_id, fund_id = -1, amount = 0, target_id = -1, target_fund = -1;
        string first_name, last_name;

        // Read the transaction type first
        if (!(iss >> type)) {
            // Failed to read the transaction type, handle error
            cerr << "Error reading transaction type from line: " << line << endl;
            continue; // Skip to the next line
        }

        // Depending on the transaction type, read the remaining fields
        if (type == 'O') {
            iss >> account_id >> last_name >> first_name;
            transactions.push(Transaction(type, account_id, -1, 0, -1, -1, first_name, last_name));
        } else if (type == 'D' || type == 'W') {
            iss >> account_id >> fund_id >> amount;
            transactions.push(Transaction(type, account_id, fund_id, amount));
        } else if (type == 'T') {
            iss >> account_id >> fund_id >> target_id >> target_fund >> amount;
            transactions.push(Transaction(type, account_id, fund_id, amount, target_id, target_fund));
        } else if (type == 'H') {
            iss >> account_id;
            transactions.push(Transaction(type, account_id));
        } else if (type == 'F') {
            iss >> account_id >> fund_id;
            transactions.push(Transaction(type, account_id, fund_id));
        } else {
            // Invalid transaction type, handle error
            cerr << "Invalid transaction type: " << type << " in line: " << line << endl;
        }
    }
}


void Bank::ProcessTransactions() {
    while (!transactions.empty()) {
        Transaction &transaction = transactions.front();
        transaction.Process(*this);
        transactions.pop();
    }

}

void Bank::PrintAccounts() const {
    accounts.Display();
}

bool Bank::SetAccount(Account *account) {
    return accounts.Insert(account);
}

BSTree &Bank::GetAccount() {
    return accounts;
}




