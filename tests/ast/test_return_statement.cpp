#include "ast/return_statement.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <memory>

void test_return_statement_string()
{
	std::cout << "Testing ReturnStatement string representation...\n";

	Token return_token(TokenType::RETURN, "return");

	auto return_stmt = std::make_unique<ReturnStatement>(return_token);

	std::string expected = "return ;";
	std::string actual = return_stmt->get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_return_statement_string: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_return_statement_string: passed\n";
}
