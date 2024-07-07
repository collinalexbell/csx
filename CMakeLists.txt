cmake_minimum_required(VERSION 3.10)
project(csx C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(csx
    src/main.c
    src/lexer.c
    src/parser.c
    src/codegen.c
)
