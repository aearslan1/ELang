cmake_minimum_required(VERSION 3.20)

project(ELang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ELang
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
)

target_include_directories(ELang PRIVATE include)
