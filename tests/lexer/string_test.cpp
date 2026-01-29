#include <gtest/gtest.h>
#include "lexer/lexer.hpp"

TEST(LexerTest, TestStringLiteral)
{
	std::string input = R"(
		"foobar"
		"foo bar"
	)";

	struct Test
	{
		TokenType expected_type;
		std::string expected_literal;
	};

	std::vector<Test> tests = {
		{TokenType::STRING, "foobar"},
		{TokenType::STRING, "foo bar"},
		{TokenType::E_O_F, ""},
	};

	Lexer l(input);

	for (const auto &tt : tests)
	{
		Token tok = l.next_token();
		EXPECT_EQ(tok.type, tt.expected_type);
		EXPECT_EQ(tok.literal, tt.expected_literal);
	}
}
