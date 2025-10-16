#include "ast/expression_statement.hpp"
#include <format>
#include <iostream>
#include <memory>

void test_expression_statement_string()
{
	std::cout << "Testing ExpressionStatement string representation...\n";

	auto expr_stmt = std::make_unique<ExpressionStatement>();

	std::string expected = "";
	std::string actual = expr_stmt->get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_expression_statement_string: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_expression_statement_string: passed\n";
}
