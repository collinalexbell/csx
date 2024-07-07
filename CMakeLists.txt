cmake_minimum_required(VERSION 3.10)
project(csx C)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Installation prefix" FORCE)
endif()

set(CMAKE_C_STANDARD 11)

include_directories(include)

# Add Unity framework
include(FetchContent)
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

# Main executable
add_executable(csx
    src/main.c
    src/lexer.c
    src/parser.c
    src/codegen.c
)

# Test executable
add_executable(test_lexer
    test/test_lexer.c
    src/lexer.c
)
target_link_libraries(test_lexer unity)

# Installation rules
install(TARGETS csx RUNTIME DESTINATION bin)

# Enable testing
enable_testing()
add_test(NAME LexerTest COMMAND test_lexer)
