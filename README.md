# Jolly-Banker
A banking application which processes transactions

This banking application consists of three phases.
1) The program will read in a string of transactions from a file into a queue. These transactions can open
accounts, withdraw funds, deposit funds, transfer funds, or ask for the transactional history to be printed.
2) The program will next read from the queue and process the transactions in order.
3) When the queue has been depleted the program will print out all open accounts and balances in those
accounts.

## Input
To test your program a file will be passed in by argument to the program on the command line. The file will
contain a list of transactions that need to be executed. Transactions of the format described below (see
section on transactions) will be contained in this file. There will be one transaction per line. Assume that the
input is well-formed in the file—that is, there are no syntax errors.
That said, there may be errors in the transactions themselves. For instance, a transaction may try to withdraw
more money than there is a fund or try to withdraw for a non-existent fund. See the Errors section below for
details.

## Client Accounts and Funds
Each client account contains assets held in up to nine funds. A client account is represented by a first and last
name (two strings) and a unique id (integer).
Each fund is indicated by an id from 0-8. The eight funds that each account has are as follows:
Fund 0: Money Market
Fund 1: Prime Money Market
Fund 2: Long-Term Bond
Fund 3: Short-Term Bond
Fund 4: S & P 500 Index Fund
Fund 5: Capital Value Fund
Fund 6: Growth Equity Fund
Fund 7: Growth Index Fund
Fund 8: International Markets Fund
All client accounts are opened with an open transaction, indicated by the letter O (see below).

## Transactions
There are six types of transactions and each is identified by a character at the beginning of the line.
O: Open a client account. Each new account gets 200 in the Money Market Fund (fund 0)
D: Deposit assets into a fund
W: Withdraw assets from a fund
T: Transfer assets between funds (can be funds owned by a single client or transfers between clients)
H: Display the history of all transactions for a client account
F: Display the history for all transactions of a given fund. The format for the commands consists of a
transaction type (above), followed by an account id, fund id, and amount. For transfers, the "from" account
and fund comes before the "to" account and fund.

## Example Transactions
D 1234 1 100 // Deposit $100 into the prime money market account of client ID 1234
W 1234 0 500 // Withdraw $500 from the money market of client ID 1234.
T 1234 0 1234 1 1000 // Transfer $1000 from client 1234's money market to the prime money market.
T 1234 0 5678 0 1000 // Transfer $1000 from 1234's money market to 5678's money market.
H 1234 // Display the history of all transactions of all accounts for client 1234.
F 1234 4 // Display the history for all transactions on the 500 Index Fund for client 1234
O 6537 Bowden Charles // Open an account for client Charles Bowden. Use account id 6537.

## Errors
You can assume the input transaction's format (transaction type, number and types of input items) are correct.
However, the program should deal with all other types of logical and semantic errors. For instance, there could
be a bad account number (for instance, one already used) or an amount which is too much to withdraw.
Assume that each line will begin with an appropriate letter: O, W, D, T, H and F.
Example errors which may occur
W 6543 6 10000 // trying to withdraw 10000 when the Growth Equity fund of client 6543 has only $20
D 7654 76 1000 // client account 7654 does not exist
T 1451 4 1451 6 2000 // trying to transfer 2000 from the S & P 500 Index fund of client 1451 when that fund has only $500
A transaction that would cause a balance to become negative should not occur and is an error (A withdrawal
or transfer of $0 is fine). There is one exception to this rule: if you are withdrawing from a money market fund
with insufficient dollars, and it can be covered with dollars from the other money market fund owned by the
client account, the desired amount (only the partial amount needed to cover the withdrawal) is moved to that
money market account. The two Bond accounts are handled similarly. If one is transferring between two linked
funds (say, 0 and 1) then the transaction should only succeed if the fund being withdrawn from has enough
funds. No other types of accounts are handled in this manner.
Appropriate error messages should be printed out to cerr. No other messages should be printed out during
phase 1 or phase 2.

## Output
In Phase 3, each open client account will be printed out with the amount held in each account. Please make
sure to create an intuitive and readable output for this aspect of the program. This output format should be
part of your design.

