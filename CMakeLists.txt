cmake_minimum_required(VERSION 3.28)
project(Tema2SD)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tema2SD SkipList.cpp
        RBTree.cpp
        main.cpp
        AVL.cpp)
