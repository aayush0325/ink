#include "lexer/lexer.hpp"
#include "tests/lexer/test.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <vector>

void test_basic_TokenType()
{
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
	bool success = true;

	for (auto &expected : expected_results)
	{
		Token actual = lexer.next_token();
		if (actual != expected)
		{
			success = false;
			std::cout << std::format("testcase {}: failed - expected token type '{}', got '{}'\n",
									 tc, static_cast<int>(expected.type), static_cast<int>(actual.type));
		}
		tc++;
	}

	if (success)
		std::cout << std::format("lexer tests for basic code: passed\n");
}