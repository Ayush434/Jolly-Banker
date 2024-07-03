//
// Created by ayush on 5/21/2024.
//

#include "Transaction.h"
#include "Account.h" // Add this include directive
#include "Bank.h"

#include <iostream>
using namespace std;


Transaction::Transaction(char type, int account_id, int fund_id, int amount, int target_id, int target_fund,
                         const string &first_name, const string &last_name):
                         type(type), account_id(account_id), fund_id(fund_id), amount(amount), target_id(target_id),
                         target_fund(target_fund), first_name(first_name), last_name(last_name) {}

void Transaction::Process(Bank &bank) {
    Account *account = nullptr;
    if (type == 'O') {
        // Open account
        auto *new_account = new Account(account_id, first_name, last_name);
        if(bank.SetAccount(new_account)){
            new_account->RecordTransaction(*this);
        }else{
            // Invalid transaction type, handle error
            cerr << "Client Account " << account_id << " already open. Transaction refused" << endl;
        }

    } else if (type == 'D') {
        // Deposit
        if (bank.GetAccount().Retrieve(account_id, account)) {
            account->Deposit(fund_id, amount);
            account->RecordTransaction(*this); // Record the transaction
        }else{
            // Invalid transaction type, handle error
            cerr << "Client Account " << account_id << " not found. Deposit failed" << endl;
        }
    } else if (type == 'W') {
        // Withdraw
        if (bank.GetAccount().Retrieve(account_id, account)) {
            account->Withdraw(fund_id, amount);
            account->RecordTransaction(*this); // Record the transaction
        }else{
            // Invalid transaction type, handle error
            cerr << "Client Account " << account_id << " not found. Withdraw failed" << endl;
        }
    } else if (type == 'T') {
        // Transfer
        Account *target_account = nullptr;
        if (bank.GetAccount().Retrieve(account_id, account)) {
            if(bank.GetAccount().Retrieve(target_id, target_account)){
                account->Transfer(fund_id, target_fund, amount, *target_account);
                account->RecordTransaction(*this); // Record the transaction
                if(account_id != target_id){
                    target_account->RecordTransaction(*this);
                }

            }else{
                // Invalid transaction type, handle error
                cerr << "Target Account " << target_id << " not found. Transfer refused" << endl;
            }
        }else{
            // Invalid transaction type, handle error
            cerr << "Client Account " << account_id << " not found. Transfer failed" << endl;
        }

    } else if (type == 'H') {
        // Display history
        if (bank.GetAccount().Retrieve(account_id, account)) {
            cout << "\nTransaction History of ";
            account->Print();
        }else{
            // Invalid transaction type, handle error
            cerr << "Client Account " << account_id << " not found. History transaction refused" << endl;
        }

    } else if (type == 'F') {
        // Display fund history
        if (bank.GetAccount().Retrieve(account_id, account)) {
            string funds_name = account->GetFundName(fund_id);
            string first_name = account->GetFirstName();
            string last_name = account->GetLastName();

            std::cout << "\nTransaction History for " << first_name << " " << last_name << " " <<
                      funds_name << ":" << std::endl;
            account->GetFundHistory(fund_id);
        }else{
            // Invalid transaction type, handle error
            cerr << "Client Account " << account_id << " not found. Fund History transaction refused" << endl;
        }
    }
}

void Transaction::Display() const {

    if(type == 'O'){
        cout << "     " << type << " " << account_id << " " << last_name << " " << first_name <<endl;
    }else if (type == 'D') {
        cout << "     " << type << " " << account_id << " " << fund_id << " " << amount <<endl;
    } else if (type == 'W') {
        cout << "     " << type << " " << account_id << " " << fund_id << " " << amount <<endl;
    } else if (type == 'T') {
        cout << "     " << type << " " << account_id << " " << fund_id << " " <<
        target_id << " " << target_fund<<" " << amount <<endl;
    } else if (type == 'H') {
        cout << "     " << type << " " << account_id << endl;
    } else if (type == 'F') {
        cout << "     " << type << " " << account_id << " " << fund_id  <<endl;
    }

}

int Transaction::GetAccountId() const {
    return account_id;
}

int Transaction::GetFundId() const {
    return fund_id;
}

int Transaction::GetTargetFundId() const {
    return target_fund;
}


