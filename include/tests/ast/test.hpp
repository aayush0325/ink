#pragma once

// Individual AST test functions
void test_identifier_string();
void test_let_statement_string();
void test_return_statement_string();
void test_expression_statement_string();
void test_program_string();
void test_program_multiple_statements();
void test_empty_program();

// Main test runner
void run_all_ast_string_tests();
