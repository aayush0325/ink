#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <gtest/gtest.h>
#include <format>

struct GroupedTest
{
	std::string input;
	std::string expected;
};

TEST(ParserTest, GroupedExpressions)
{
	std::vector<GroupedTest> tests = {
		{"1 + (2 + 3) + 4",
		 "((1 + (2 + 3)) + 4)"},
		{"(5 + 5) * 2",
		 "((5 + 5) * 2)"},
		{"2 / (5 + 5)",
		 "(2 / (5 + 5))"},
		{"-(5 + 5)",
		 "(-(5 + 5))"},
		{"!(true == true)",
		 "(!(true == true))"}};

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

