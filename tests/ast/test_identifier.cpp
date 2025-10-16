#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>

void test_identifier_string()
{
	std::cout << "Testing Identifier string representation...\n";

	Token ident_token(TokenType::IDENT, "myVar");
	Identifier identifier(ident_token, "myVar");

	std::string expected = "myVar";
	std::string actual = identifier.get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_identifier_string: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_identifier_string: passed\n";
}
