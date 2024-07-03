//
// Created by ayush on 5/21/2024.
// Transaction class stores the transaction details like type of transaction, id's of account, fund
// , target account, target fund, amount, first and last name. It processes each transaction and throw error when
// transaction is invalid. It displays each transaction. There are some getters defined as needed
// by other classes like GetFundId, GetAccountId and GetTargetFundId.
//

#ifndef JOLLYBANKER_TRANSACTION_H
#define JOLLYBANKER_TRANSACTION_H

#include <string>
#include "Bank.h"
#include "BSTree.h"

class Bank;

// Represents a financial transaction
class Transaction {
public:
    // Constructor to initialize a transaction
    // Parameters specify the type of transaction, account and fund IDs, amounts, and optionally names
    Transaction(char type, int account_id, int fund_id = -1, int amount = 0, int target_id = -1, int target_fund = -1,
                const std::string &first_name = "", const std::string &last_name = "");

    // Processes the transaction using the provided bank instance
    void Process(Bank &bank);

    // Displays the details of the transaction in a nice way
    void Display() const;

    // Getters for transaction details
    int GetAccountId() const;
    int GetFundId() const;
    int GetTargetFundId() const;

private:
    char type; // Type of transaction: O, D, W, T, H, F
    int account_id; // ID of the account associated with the transaction
    int fund_id; // ID of the fund associated with the transaction
    int amount; // Amount of money involved in the transaction
    int target_id; // ID of the target account for transfers
    int target_fund; // ID of the target fund for transfers
    std::string first_name; // First name of the client (for opening accounts)
    std::string last_name; // Last name of the client (for opening accounts)
};


#endif //JOLLYBANKER_TRANSACTION_H
