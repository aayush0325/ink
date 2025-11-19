#pragma once

#include <memory>
#include "ast/ast.hpp"
#include "parser/parser.hpp"
#include <string>

void test_let_statement_noexpr();
void test_return_statement();
void check_parser_errors(Parser &parser);
bool test_boolean_literal(ast::Expression *exp, bool expected_value);
void check_identifier_expression_statements();
void check_integer_literal_statement();
void check_boolean_literal_statement();
void check_false_boolean_literal_statement();
void check_prefix_expressions();
void check_operator_precedence_parsing();
void check_infix_expressions();
void check_grouped_expressions();
void check_if_expressions();
void check_function_literal();
void check_function_parameter_parsing();