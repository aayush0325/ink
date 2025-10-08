#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "tests/lexer/test.hpp"
#include "types/types.hpp"
#include <vector>
#include <iostream>

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
			std::cout << "Error in test case: " << tc << " ";
			std::cout << "Expected Token type: " << expected.type << " Actual Token type: " << actual.type << std::endl;
		}
		tc++;
	}

	if (success)
		std::cout << "lexer tests for basic code passed!" << std::endl;
}