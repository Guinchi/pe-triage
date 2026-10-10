cmake_minimum_required(VERSION 3.20)
project(pe_triage LANGUAGES C)

# Use standard C11 with no compiler-specific extensions
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# The program and the source files that build it
add_executable(pe-triage src/main.c)

# Strict warnings on every compiler
if(MSVC)
    target_compile_options(pe-triage PRIVATE /W4)
else()
    target_compile_options(pe-triage PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

enable_testing()

# Running with no arguments should exit with an error, so failing is the expected result
add_test(NAME no_args_exits_with_error COMMAND pe-triage)
set_tests_properties(no_args_exits_with_error PROPERTIES WILL_FAIL TRUE)