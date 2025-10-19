#include "ast/return_statement.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <memory>

void test_return_statement_string()
{
	std::cout << "Test for return statement string representation\n";
	std::cout << "Test starting\n";

	Token return_token(TokenType::RETURN, "return");

	auto return_stmt = std::make_unique<ast::ReturnStatement>(return_token);

	std::string expected = "return ;";
	std::string actual = return_stmt->get_string();
	int error_count = 0;

	if (actual != expected)
	{
		error_count++;
		std::cout << std::format("Failed - expected '{}', got '{}'\n",
								 expected, actual);
	}

	if (error_count == 0)
		std::cout << "Test for return statement string representation ended (all passed)\n\n";
	else
		std::cout << std::format("Test for return statement string representation ended ({} errors)\n\n", error_count);
}
