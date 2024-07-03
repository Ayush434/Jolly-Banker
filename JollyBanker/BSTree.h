//
// Created by ayush on 5/21/2024.
// BSTree class stores the account details like id, name, funds balances and history.
// It has functions to insert, retrieve, delete and display accounts.
// It has destructor to delete the accounts, copy constructor to copy new BSTree containing accounts, and
// assignment operator to assign new account details to existing one. It has some helper functions
// to make the work easier for other functions like copy tree, in-order traversal and more.

#ifndef JOLLYBANKER_BSTREE_H
#define JOLLYBANKER_BSTREE_H



class Account;

// Represents a binary search tree to manage and store accounts
class BSTree {
public:
    // Default constructor to initialize an empty tree
    BSTree();

    // Copy constructor to initialize tree as a copy of another tree
    BSTree(const BSTree& tree);

    // Destructor to clean up allocated memory
    ~BSTree();

    // Inserts an account into the tree
    // Returns true if the account was added successfully
    // Returns false if the account number already exists
    bool Insert(Account *account);

    // Retrieves an account from the tree by its ID
    // First parameter is the ID of the account
    // Second parameter holds pointer to found account, NULL if not found
    bool Retrieve(const int& account_id, Account* &account) const;

    // Deletes an account from the tree by its ID
    // First parameter is the ID of the account
    // Second parameter holds pointer to found account, NULL if not found
    bool Delete(const int& account_id, Account* &account);

    // Assignment operator to assign one tree to another
    BSTree& operator=(const BSTree& tree);

    // Displays the contents of the tree to cout
    void Display() const;

    // Returns the number of nodes in the tree
    int Size() const;

private:
    // Represents a node in the binary search tree
    struct Node {
        Account* p_acct; // Pointer to the account stored in the node
        Node* right; // Pointer to the right child
        Node* left; // Pointer to the left child
    };

    Node* _root; // Root node of the tree
    int _size;

    void InOrderTraversal(Node *root) const;

    Node *CopyTree(Node *root);

    Node *GetSuccessor(Node *node);

    void DisplayAccountDetails(Account *account) const;
};


#endif //JOLLYBANKER_BSTREE_H
