#include "lexer/lexer.hpp"
#include "tests/lexer/test.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <vector>

TEST(LexerTest, FullCodeSampleTokenizer)
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

	for (size_t i = 0; i < expected_results.size(); i++)
	{
		Token actual = lexer.next_token();
		EXPECT_EQ(expected_results[i], actual)
			<< "Token mismatch at index " << i;
	}
}
