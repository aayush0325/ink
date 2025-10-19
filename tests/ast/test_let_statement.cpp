#include "ast/let_statement.hpp"
#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <memory>

void test_let_statement_string()
{
	std::cout << "Test for let statement string representation\n";
	std::cout << "Test starting\n";

	Token let_token(TokenType::LET, "let");
	Token ident_token(TokenType::IDENT, "myVar");

	auto let_stmt = std::make_unique<ast::LetStatement>(let_token);
	let_stmt->ident = std::make_unique<ast::Identifier>(ident_token, "myVar");

	std::string expected = "let myVar;";
	std::string actual = let_stmt->get_string();
	int error_count = 0;

	if (actual != expected)
	{
		error_count++;
		std::cout << std::format("Failed - expected '{}', got '{}'\n",
								 expected, actual);
	}

	if (error_count == 0)
		std::cout << "Test for let statement string representation ended (all passed)\n\n";
	else
		std::cout << std::format("Test for let statement string representation ended ({} errors)\n\n", error_count);
}
