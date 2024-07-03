#include <iostream>
#include "Bank.h"

int main() {
    Bank bank;
    bank.ReadTransactions("C:\\Users\\ayush\\CLionProjects\\JollyBanker\\test2.txt");
    bank.ProcessTransactions();

    std::cout << "\nAccount Balances \n"<<std::endl;
    bank.PrintAccounts();
    return 0;
}
