#include "lexer/lexer.hpp"
#include "tests/lexer/test.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <vector>

void test_basic_TokenType()
{
	std::cout << "Test for basic token type recognition\n";
	std::cout << "Test starting\n";

	std::string input = "      =+(){},;";
	std::vector<Token> expected_results = {
		Token(TokenType::ASSIGN, "="),
		Token(TokenType::PLUS, "+"),
		Token(TokenType::LPAREN, "("),
		Token(TokenType::RPAREN, ")"),
		Token(TokenType::LBRACE, "{"),
		Token(TokenType::RBRACE, "}"),
		Token(TokenType::COMMA, ","),
		Token(TokenType::SEMICOLON, ";"),
	};

	Lexer lexer = Lexer(input);
	u16 tc = 1;
	int error_count = 0;

	for (auto &expected : expected_results)
	{
		Token actual = lexer.next_token();
		if (actual != expected)
		{
			error_count++;
			std::cout << std::format("Failed - testcase {}: expected token type '{}', got '{}'\n",
									 tc, static_cast<int>(expected.type), static_cast<int>(actual.type));
		}
		tc++;
	}

	if (error_count == 0)
		std::cout << std::format("Test for basic token type recognition ended (all passed)\n\n");
	else
		std::cout << std::format("Test for basic token type recognition ended ({} errors)\n\n", error_count);
}