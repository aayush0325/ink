#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>

void test_identifier_string()
{
	std::cout << "Test for identifier string representation\n";
	std::cout << "Test starting\n";

	Token ident_token(TokenType::IDENT, "myVar");
	ast::Identifier identifier(ident_token, "myVar");

	std::string expected = "myVar";
	std::string actual = identifier.get_string();
	int error_count = 0;

	if (actual != expected)
	{
		error_count++;
		std::cout << std::format("Failed - expected '{}', got '{}'\n",
								 expected, actual);
	}

	if (error_count == 0)
		std::cout << "Test for identifier string representation ended (all passed)\n\n";
	else
		std::cout << std::format("Test for identifier string representation ended ({} errors)\n\n", error_count);
}
