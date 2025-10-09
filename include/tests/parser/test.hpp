#pragma once

#include <memory>
#include "ast/ast.hpp"
#include <string>

void test_let_statement_noexpr();

void test_let_statement(const std::unique_ptr<Statement> &stmt, const std::string &expected_identifier_name, const int &tc);