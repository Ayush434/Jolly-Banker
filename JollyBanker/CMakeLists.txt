cmake_minimum_required(VERSION 3.28)
project(JollyBanker)

set(CMAKE_CXX_STANDARD 17)

add_executable(JollyBanker main.cpp
        Transaction.cpp
        Transaction.h
        Account.cpp
        Account.h
        Bank.cpp
        Bank.h
        BSTree.cpp
        BSTree.h
)
