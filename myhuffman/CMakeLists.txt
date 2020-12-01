cmake_minimum_required(VERSION 3.17)
project(myhuffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(myhuffman main.cpp HuffmanTree.cpp HuffmanTree.h  Queue.h Queue.cpp)