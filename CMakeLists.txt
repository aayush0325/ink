cmake_minimum_required(VERSION 3.10)
project(ink)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Exports compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# STEP 1: Collect all implementation files (excluding main.cpp files)
# This creates a library with shared code that both executables can use
file(GLOB_RECURSE LIB_FILES src/*.cpp)
list(FILTER LIB_FILES EXCLUDE REGEX ".*main\\.cpp$")

# STEP 2: Create a static library from implementation files
# This allows code reuse without duplicate main() functions
add_library(interpretr_lib STATIC ${LIB_FILES})

# STEP 3: Create the main executable
# Links only src/main.cpp + the.library
add_executable(ink src/main.cpp)
target_link_libraries(ink interpretr_lib)

# STEP 4: Collect test files (excluding main.cpp from src/)
set(TEST_FILES
    tests/main.cpp
    tests/parser/test_boolean_expressions.cpp
    tests/parser/test_call_expressions.cpp
    tests/parser/test_function_literal.cpp
    tests/parser/test_grouped_expressions.cpp
    tests/parser/test_ident_expressions.cpp
    tests/parser/test_if_expressions.cpp
    tests/parser/test_infix_expressions.cpp
    tests/parser/test_integer_expressions.cpp
    tests/parser/test_let_statement_noexpr.cpp
    tests/parser/test_operator_precedence.cpp
    tests/parser/test_prefix_expressions.cpp
    tests/parser/test_return_statement.cpp
    tests/parser/test_utils.cpp
    tests/lexer/basic_tokens.cpp
    tests/lexer/code_complex.cpp
    tests/lexer/full_code.cpp
    tests/evaluator/test_boolean_evaluation.cpp
    tests/evaluator/test_error_handling.cpp
    tests/evaluator/test_if_else_evaluation.cpp
    tests/evaluator/test_let_statements.cpp
    tests/evaluator/test_functions.cpp
    tests/evaluator/test_if_else_integer_evaluation.cpp
    tests/evaluator/test_integer_evaluation.cpp
    tests/ast/test_identifier.cpp
    tests/ast/test_let_statement.cpp
    tests/ast/test_program.cpp
    tests/ast/test_return_statement.cpp
)

find_package(GTest CONFIG REQUIRED)

# STEP 5: Create the test executable  
# Links test files + the library (but NOT src/main.cpp)
add_executable(tests ${TEST_FILES})
target_link_libraries(tests interpretr_lib GTest::gtest GTest::gtest_main)
