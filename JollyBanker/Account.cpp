//
// Created by ayush on 5/21/2024.
//


#include <iostream>
#include "Account.h"
#include "Transaction.h"
#include <vector>

Account::Account(int id, const std::string &first_name, const std::string &last_name) {
    this->id = id;
    this->first_name = first_name;
    this->last_name = last_name;
    this->funds = std::vector<int>(9, 0);
    Deposit(0, 200);
}

void Account::Deposit(int fund_id, int amount) {
    funds[fund_id] += amount;
}

void Account::Withdraw(int fund_id, int amount) {
    if (funds[fund_id] >= amount) {
        funds[fund_id] -= amount;
    } else if (fund_id == 0 || fund_id == 1) { // Money market funds
        int other_fund_id = (fund_id == 0) ? 1 : 0;
        int total_balance = funds[fund_id] + funds[other_fund_id];
        if (total_balance >= amount) {
            int needed_from_other_fund = amount - funds[fund_id];
            funds[fund_id] = 0;
            funds[other_fund_id] -= needed_from_other_fund;
        } else {
            std::string fund_name = GetFundName(fund_id);
            std::cerr << "Insufficient funds for withdrawal of " << amount << " from " << first_name << " " << last_name << " " << fund_name << std::endl;
        }
    } else if (fund_id == 2 || fund_id == 3) { // Bond funds
        int other_fund_id = (fund_id == 2) ? 3 : 2;
        int total_balance = funds[fund_id] + funds[other_fund_id];
        if (total_balance >= amount) {
            int needed_from_other_fund = amount - funds[fund_id];
            funds[fund_id] = 0;
            funds[other_fund_id] -= needed_from_other_fund;
        } else {
            std::string fund_name = GetFundName(fund_id);
            std::cerr << "Insufficient funds for withdrawal of " << amount << " from " << first_name << " " << last_name << " " << fund_name << std::endl;
        }
    } else {
        std::string fund_name = GetFundName(fund_id);
        std::cerr << "Insufficient funds for withdrawal of " << amount << " from " << first_name << " " << last_name << " " << fund_name << std::endl;
    }
}

void Account::Transfer(int from_fund_id, int to_fund_id, int amount, Account &target_account) {
    if (funds[from_fund_id] >= amount) {
        funds[from_fund_id] -= amount;
        target_account.Deposit(to_fund_id, amount);
    } else if (from_fund_id == 0 || from_fund_id == 1) { // Money market funds
        int other_fund_id = (from_fund_id == 0) ? 1 : 0;
        int total_balance = funds[from_fund_id] + funds[other_fund_id];
        if (total_balance >= amount) {
            int needed_from_other_fund = amount - funds[from_fund_id];
            funds[from_fund_id] = 0;
            funds[other_fund_id] -= needed_from_other_fund;
            target_account.Deposit(to_fund_id, amount);
        } else {
            std::string fund_name = GetFundName(from_fund_id);
            std::cerr << "Insufficient funds for transfer of " << amount << " from " << first_name << " " << last_name << " " << fund_name << std::endl;
        }
    } else if (from_fund_id == 2 || from_fund_id == 3) { // Bond funds
        int other_fund_id = (from_fund_id == 2) ? 3 : 2;
        int total_balance = funds[from_fund_id] + funds[other_fund_id];
        if (total_balance >= amount) {
            int needed_from_other_fund = amount - funds[from_fund_id];
            funds[from_fund_id] = 0;
            funds[other_fund_id] -= needed_from_other_fund;
            target_account.Deposit(to_fund_id, amount);
        } else {
            std::string fund_name = GetFundName(from_fund_id);
            std::cerr << "Insufficient funds for transfer of " << amount << " from " << first_name << " " << last_name << " " << fund_name << std::endl;
        }
    } else {
        std::string fund_name = GetFundName(from_fund_id);
        std::cerr << "Insufficient funds for transfer of " << amount << " from " << first_name << " " << last_name << " " << fund_name << std::endl;
    }
}

void Account::Print() const {
    std::cout << first_name << " " << last_name << " Account ID: " << id << std::endl;

    for (size_t i = 0; i < funds.size(); ++i) {
        if (funds[i] > 0) {
            std::cout << "    " << funds_name[i] << ": $" << funds[i] << std::endl;
            GetFundHistory(i);
        }
    }
}

void Account::GetFundHistory(int fund_id) const {
    for (const auto &transaction : fund_history) {
        if (transaction.GetFundId() == fund_id || transaction.GetTargetFundId() == fund_id) {
            transaction.Display();
        }
    }
}

void Account::PrintAccounts() const {
    std::cout << first_name << " " << last_name << " Account ID: " << id << std::endl;
    for (size_t i = 0; i < funds.size(); ++i) {
        std::cout << "  " << funds_name[i] << ": $" << funds[i] << std::endl;
    }
}

void Account::RecordTransaction(const Transaction &transaction) {
    fund_history.push_back(transaction);
}

int Account::GetId() const {
    return id;
}

std::string Account::GetFirstName() const {
    return first_name;
}

std::string Account::GetLastName() const {
    return last_name;
}

std::string Account::GetFundName(int fund_id) const {
    return funds_name[fund_id];
}
