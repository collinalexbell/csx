cmake_minimum_required(VERSION 3.10)
project(csx C)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Installation prefix" FORCE)
endif()
set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(csx
    src/main.c
    src/lexer.c
    src/parser.c
    src/codegen.c
)
# Installation rules
install(TARGETS csx RUNTIME DESTINATION bin)
