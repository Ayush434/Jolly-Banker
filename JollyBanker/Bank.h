//
// Created by ayush on 5/21/2024.
// Bank class initializes the BSTree to store accounts and queue to read/process transactions.
// It reads the trasnactions, processes them, print the account details, create new accounts and
// get the opened accounts.

#ifndef JOLLYBANKER_BANK_H
#define JOLLYBANKER_BANK_H


#include <queue>
#include <string>
#include "BSTree.h"
#include "Transaction.h"

class Transaction;
class Account;

// Represents the main banking system
class Bank {
public:
    // Constructor to initialize an empty bank
    Bank();

    // Reads transactions from a file and adds them to the transaction queue
    void ReadTransactions(const std::string &filename);

    // Processes all transactions in the queue
    void ProcessTransactions();

    // Prints all accounts and their balances
    void PrintAccounts() const;

    // Setter for accounts
    bool SetAccount(Account *account);

    // Getter for accounts
    BSTree& GetAccount();

private:
    BSTree accounts; // Binary search tree to store client accounts
    std::queue<Transaction> transactions; // Queue to store transactions to be processed
};

#endif //JOLLYBANKER_BANK_H
