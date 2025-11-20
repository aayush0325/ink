#include <gtest/gtest.h>

#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "types/types.hpp"

TEST(LexerTest, BasicInputTokenizer)
{
	std::string input = "      =+(){},;";
	std::vector<Token> expected = {
		Token(TokenType::ASSIGN, "="),
		Token(TokenType::PLUS, "+"),
		Token(TokenType::LPAREN, "("),
		Token(TokenType::RPAREN, ")"),
		Token(TokenType::LBRACE, "{"),
		Token(TokenType::RBRACE, "}"),
		Token(TokenType::COMMA, ","),
		Token(TokenType::SEMICOLON, ";"),
	};

	Lexer lexer(input);

	for (size_t i = 0; i < expected.size(); ++i)
	{
		Token actual = lexer.next_token();
		EXPECT_EQ(actual.type, expected[i].type)
			<< "Token type mismatch at index " << i;

		EXPECT_EQ(actual.literal, expected[i].literal)
			<< "Token literal mismatch at index " << i;
	}
}
