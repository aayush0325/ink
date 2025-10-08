#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "tests/lexer/test.hpp"
#include "types/types.hpp"
#include <vector>
#include <iostream>

void test_full_code()
{
	std::string input = R"(
		let five = 5;
		let ten = 10;
		let add = fn(x, y) {
			x + y;
		};
		let result = add(five, ten);
	)";

	std::vector<Token> expected_results = {
		Token(TokenType::LET, "let"),
		Token(TokenType::IDENT, "five"),
		Token(TokenType::ASSIGN, "="),
		Token(TokenType::INT, "5"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::LET, "let"),
		Token(TokenType::IDENT, "ten"),
		Token(TokenType::ASSIGN, "="),
		Token(TokenType::INT, "10"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::LET, "let"),
		Token(TokenType::IDENT, "add"),
		Token(TokenType::ASSIGN, "="),
		Token(TokenType::FUNCTION, "fn"),
		Token(TokenType::LPAREN, "("),
		Token(TokenType::IDENT, "x"),
		Token(TokenType::COMMA, ","),
		Token(TokenType::IDENT, "y"),
		Token(TokenType::RPAREN, ")"),
		Token(TokenType::LBRACE, "{"),
		Token(TokenType::IDENT, "x"),
		Token(TokenType::PLUS, "+"),
		Token(TokenType::IDENT, "y"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::RBRACE, "}"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::LET, "let"),
		Token(TokenType::IDENT, "result"),
		Token(TokenType::ASSIGN, "="),
		Token(TokenType::IDENT, "add"),
		Token(TokenType::LPAREN, "("),
		Token(TokenType::IDENT, "five"),
		Token(TokenType::COMMA, ","),
		Token(TokenType::IDENT, "ten"),
		Token(TokenType::RPAREN, ")"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::E_O_F, ""),
	};

	Lexer lexer = Lexer(input);
	u16 tc = 1;

	bool success = true;

	for (auto &expected : expected_results)
	{
		Token actual = lexer.next_token();
		if (actual != expected)
		{
			std::cout << "Error in test case: " << tc << " ";
			std::cout << "Expected Token type: " << expected.type << " (" << expected.literal << ") ";
			std::cout << "Actual Token type: " << actual.type << " (" << actual.literal << ")" << std::endl;
		}
		tc++;
	}

	if (success)
		std::cout << "lexer tests for full code passed!" << std::endl;
}
