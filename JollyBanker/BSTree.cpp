//
// Created by ayush on 5/21/2024.
//

#include "BSTree.h"
#include "Account.h" // Add this include directive

#include <iostream>

// Default constructor
BSTree::BSTree() : _root(nullptr), _size(0) {}

// Copy constructor
BSTree::BSTree(const BSTree& tree) {
    _root = nullptr;
    _size = 0;
    *this = tree; // Use the assignment operator to copy the tree
}

// Destructor
BSTree::~BSTree() {
    // Call a helper function to recursively delete all nodes
    while (_root != nullptr) {
        Delete(_root->p_acct->GetId(), _root->p_acct);
    }
}

// Insert method
bool BSTree::Insert(Account *account) {
    Node* newNode = new Node;
    newNode->p_acct = account;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (_root == nullptr) {
        _root = newNode;
        _size++;
        return true;
    }

    Node* current = _root;
    Node* parent = nullptr;
    while (true) {
        parent = current;
        if (account->GetId() < current->p_acct->GetId()) {
            current = current->left;
            if (current == nullptr) {
                parent->left = newNode;
                _size++;
                return true;
            }
        } else if (account->GetId() > current->p_acct->GetId()) {
            current = current->right;
            if (current == nullptr) {
                parent->right = newNode;
                _size++;
                return true;
            }
        } else { // Duplicate account ID
            delete newNode;
            return false;
        }
    }
}

// Retrieve method
bool BSTree::Retrieve(const int& account_id, Account* &account) const {
    Node* current = _root;
    while (current != nullptr) {
        if (account_id == current->p_acct->GetId()) {
            account = current->p_acct;
            return true;
        } else if (account_id < current->p_acct->GetId()) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    account = nullptr;
    return false;
}

// Delete method
bool BSTree::Delete(const int& account_id, Account* &account) {
    Node* parent = nullptr;
    Node* current = _root;
    bool isLeftChild = true;

    while (current->p_acct->GetId() != account_id) {
        parent = current;
        if (account_id < current->p_acct->GetId()) {
            isLeftChild = true;
            current = current->left;
        } else {
            isLeftChild = false;
            current = current->right;
        }
        if (current == nullptr) {
            return false; // Account not found
        }
    }

    // Case 1: No children
    if (current->left == nullptr && current->right == nullptr) {
        if (current == _root) {
            _root = nullptr;
        } else if (isLeftChild) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    }
        // Case 2: One child
    else if (current->right == nullptr) {
        if (current == _root) {
            _root = current->left;
        } else if (isLeftChild) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } else if (current->left == nullptr) {
        if (current == _root) {
            _root = current->right;
        } else if (isLeftChild) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    }
        // Case 3: Two children
    else {
        Node* successor = GetSuccessor(current);
        if (current == _root) {
            _root = successor;
        } else if (isLeftChild) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
    }

    _size--;
    account = current->p_acct;
    delete current;
    return true;
}

// Helper function to find the successor node for deletion
BSTree::Node* BSTree::GetSuccessor(Node* node) {
    Node* successorParent = node;
    Node* successor = node;
    Node* current = node->right;

    while (current != nullptr) {
        successorParent = successor;
        successor = current;
        current = current->left;
    }

    if (successor != node->right) {
        successorParent->left = successor->right;
        successor->right = node->right;
    }

    return successor;
}

// Assignment operator
BSTree& BSTree::operator=(const BSTree& tree) {
    if (this == &tree) {
        return *this;
    }
    // Clear existing tree
    this->~BSTree(); // Call destructor to clear existing tree

    // Perform deep copy of tree
    if (tree._root != nullptr) {
        // Call helper function to recursively copy nodes
        this->_root = CopyTree(tree._root);
    }
    this->_size = tree._size;
    return *this;
}

// Helper function to perform deep copy of tree
BSTree::Node* BSTree::CopyTree(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* newNode = new Node;
    newNode->p_acct = new Account(*(root->p_acct)); // Copy account object
    newNode->left = CopyTree(root->left); // Recursively copy left subtree
    newNode->right = CopyTree(root->right); // Recursively copy right subtree
    return newNode;
}


// Displays the contents of the tree (inorder traversal)
void BSTree::Display() const {
    InOrderTraversal(_root);
    std::cout << std::endl;
}

// Helper function for inorder traversal
void BSTree::InOrderTraversal(Node* root) const {
    if (root != nullptr) {
        InOrderTraversal(root->left);
        DisplayAccountDetails(root->p_acct);
        InOrderTraversal(root->right);
    }
}

// Display details of an account
void BSTree::DisplayAccountDetails(Account* account) const {

    // Display fund details
    account->PrintAccounts();
    std::cout << std::endl;
}


// Returns the number of nodes in the tree
int BSTree::Size() const {
    return _size;
}

