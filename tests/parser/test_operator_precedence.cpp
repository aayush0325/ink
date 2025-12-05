#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <gtest/gtest.h>
#include <format>

struct PrecedenceTest
{
	std::string input;
	std::string expected;
};

TEST(ParserTest, OperatorPrecedence)
{
	std::vector<PrecedenceTest> tests = {
		{"-a * b",
		 "((-a) * b)"},
		{"!-a",
		 "(!(-a))"},
		{"a + b + c",
		 "((a + b) + c)"},
		{"a + b - c",
		 "((a + b) - c)"},
		{"a * b * c",
		 "((a * b) * c)"},
		{"a * b / c",
		 "((a * b) / c)"},
		{"a + b / c",
		 "(a + (b / c))"},
		{"a + b * c + d / e - f",
		 "(((a + (b * c)) + (d / e)) - f)"},
		{"3 + 4; -5 * 5",
		 "(3 + 4)((-5) * 5)"},
		{"5 > 4 == 3 < 4",
		 "((5 > 4) == (3 < 4))"},
		{"5 < 4 != 3 > 4",
		 "((5 < 4) != (3 > 4))"},
		{"3 + 4 * 5 == 3 * 1 + 4 * 5",
		 "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
		{"true",
		 "true"},
		{"false",
		 "false"},
		{"3 > 5 == false",
		 "((3 > 5) == false)"},
		{"3 < 5 == true",
		 "((3 < 5) == true)"},
		{"a + add(b * c) + d",
		 "((a + add((b * c))) + d)"},
		{"add(a, b, 1, 2 * 3, 4 + 5, add(6, 7 * 8))",
		 "add(a, b, 1, (2 * 3), (4 + 5), add(6, (7 * 8)))"},
		{"add(a + b + c * d / f + g)",
		 "add((((a + b) + ((c * d) / f)) + g))"}};

	for (const auto &test : tests)
	{
		SCOPED_TRACE(std::format("Input: {}", test.input));
		auto lexer = std::make_unique<Lexer>(test.input);
		Parser parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		ASSERT_TRUE(program) << "Program returned nullptr";
		check_parser_errors(parser);

		std::string actual = program->get_string();
		EXPECT_EQ(actual, test.expected);
	}
}
