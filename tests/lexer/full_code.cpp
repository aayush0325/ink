#include "lexer/lexer.hpp"
#include "tests/lexer/test.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <vector>

void test_full_code()
{
	std::cout << "Test for full code tokenization\n";
	std::cout << "Test starting\n";

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
	int error_count = 0;

	for (auto &expected : expected_results)
	{
		Token actual = lexer.next_token();
		if (actual != expected)
		{
			error_count++;
			std::cout << std::format("Failed - testcase {}: expected token type '{}' "
									 "({}), got '{}' ({})\n",
									 tc, static_cast<int>(expected.type), expected.literal, static_cast<int>(actual.type), actual.literal);
		}
		tc++;
	}

	if (error_count == 0)
		std::cout << std::format("Test for full code tokenization ended (all passed)\n\n");
	else
		std::cout << std::format("Test for full code tokenization ended ({} errors)\n\n", error_count);
}
