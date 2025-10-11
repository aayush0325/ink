#include "lexer/lexer.hpp"
#include "tests/lexer/test.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <vector>

void test_code_complex()
{
	std::string input = R"(
		let five = 5;
		let ten = 10;
		let add = fn(x, y) {
			x + y;
		};
		let result = add(five, ten);
		!-/*5;
		5 < 10 > 5;
		if (5 < 10) {
			return true;
		} else {
			return false;
		}
		10 == 10;
		10 != 9;
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
		Token(TokenType::BANG, "!"),
		Token(TokenType::MINUS, "-"),
		Token(TokenType::SLASH, "/"),
		Token(TokenType::ASTERISK, "*"),
		Token(TokenType::INT, "5"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::INT, "5"),
		Token(TokenType::LT, "<"),
		Token(TokenType::INT, "10"),
		Token(TokenType::GT, ">"),
		Token(TokenType::INT, "5"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::IF, "if"),
		Token(TokenType::LPAREN, "("),
		Token(TokenType::INT, "5"),
		Token(TokenType::LT, "<"),
		Token(TokenType::INT, "10"),
		Token(TokenType::RPAREN, ")"),
		Token(TokenType::LBRACE, "{"),
		Token(TokenType::RETURN, "return"),
		Token(TokenType::TRUE, "true"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::RBRACE, "}"),
		Token(TokenType::ELSE, "else"),
		Token(TokenType::LBRACE, "{"),
		Token(TokenType::RETURN, "return"),
		Token(TokenType::FALSE, "false"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::RBRACE, "}"),
		Token(TokenType::INT, "10"),
		Token(TokenType::EQ, "=="),
		Token(TokenType::INT, "10"),
		Token(TokenType::SEMICOLON, ";"),
		Token(TokenType::INT, "10"),
		Token(TokenType::NEQ, "!="),
		Token(TokenType::INT, "9"),
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
			success = false;
			std::cout << std::format("testcase {}: failed - expected token type '{}' "
									 "({}), got '{}' ({})\n",
									 tc, static_cast<int>(expected.type),
									 expected.literal, static_cast<int>(actual.type),
									 actual.literal);
		}
		tc++;
	}

	if (success)
		std::cout << std::format("lexer tests for complex code: passed\n");
}
