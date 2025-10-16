#include "ast/let_statement.hpp"
#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <memory>

void test_let_statement_string()
{
	std::cout << "Testing LetStatement string representation...\n";

	Token let_token(TokenType::LET, "let");
	Token ident_token(TokenType::IDENT, "myVar");

	auto let_stmt = std::make_unique<LetStatement>(let_token);
	let_stmt->ident = std::make_unique<Identifier>(ident_token, "myVar");

	std::string expected = "let myVar;";
	std::string actual = let_stmt->get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_let_statement_string: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_let_statement_string: passed\n";
}
