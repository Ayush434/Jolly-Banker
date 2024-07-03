//
// Created by ayush on 5/21/2024.
// Account class stores the details of the client like id, first and last name, funds history and
// fund balances. It has functions to deposit, withdraw, and transfer funds from one fund/account to
// another. It also has some getters like getting fund history, get id, get fund name, get first and
// last name. It has additional functions to print fund transaction and fund balances, and print accounts.

#ifndef JOLLYBANKER_ACCOUNT_H
#define JOLLYBANKER_ACCOUNT_H


#include <string>
#include <vector>
#include "Transaction.h"
#include "BSTree.h"

class Transaction;
class BSTree;

// Represents a client's account which contains multiple funds
class Account {
public:
    // Constructor to initialize an account with an ID and client name
    Account(int id, const std::string &first_name, const std::string &last_name);

    // Deposits a specified amount into a specified fund
    void Deposit(int fund_id, int amount);

    // Withdraws a specified amount from a specified fund
    void Withdraw(int fund_id, int amount);

    // Transfers a specified amount from one fund to another
    void Transfer(int from_fund_id, int to_fund_id, int amount, Account &account);

    // Prints the account details, including the balance of each fund
    void Print() const;

    // Records a transaction in the fund history
    void RecordTransaction(const Transaction &transaction);

    // Retrieves the history of a specific fund
    void GetFundHistory(int fund_id) const;

    // Print accounts fund balances
    void PrintAccounts() const;

    // Getters for data members

    int GetId() const;

    std::string GetFundName(int fund_id) const;

    std::string GetFirstName() const;

    std::string GetLastName() const;



private:
    // Unique identifier for the account
    int id;
    // Client's first name
    std::string first_name;
    // Client's last name
    std::string last_name;
    // Balances of each of the 9 funds
    std::vector<int> funds;
    // History of transactions for each fund
    std::vector<Transaction> fund_history;
    // Fund account names to connect with funds balances vector
    std::vector<std::string> funds_name = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "S & P 500 Index Fund", "Capital Value Fund", "Growth Equity Fund",
                                           "Growth Index Fund", "International Market Fund"};


};


#endif //JOLLYBANKER_ACCOUNT_H
