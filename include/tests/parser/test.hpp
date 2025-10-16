#pragma once

#include <memory>
#include "ast/ast.hpp"
#include "parser/parser.hpp"
#include <string>

void test_let_statement_noexpr();
void test_return_statement();
void check_parser_errors(Parser &parser);
void check_identifier_expression_statements();