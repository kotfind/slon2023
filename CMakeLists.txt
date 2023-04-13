cmake_minimum_required(VERSION 3.16)

project(poland LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=undefined,address -g3 -O0")

add_executable(poland
    main.cpp

    MathTree.cpp
    Node.cpp
    functionList.cpp
)
