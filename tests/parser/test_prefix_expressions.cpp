#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/prefix_expression.hpp"
#include "ast/integer_literal.hpp"
#include <gtest/gtest.h>
#include <format>

struct PrefixTest
{
	std::string input;
	std::string expected_operator;
	i64 expected_integer_value;
};

TEST(ParserTest, PrefixExpressions)
{
	std::vector<PrefixTest> prefix_tests = {
		{"!5;", "!", 5},
		{"-15;", "-", 15}};

	for (const auto &test : prefix_tests)
	{
		SCOPED_TRACE(std::format("Input: {}", test.input));
		auto lexer = std::make_unique<Lexer>(test.input);
		Parser parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		ASSERT_TRUE(program) << "Program returned nullptr";
		check_parser_errors(parser);
		ASSERT_EQ(program->statements.size(), 1);

		try
		{
			auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
			auto &exp = dynamic_cast<ast::PrefixExpression &>(*stmt.expression);

			EXPECT_EQ(exp.get_prefix_operator(), test.expected_operator);

			ASSERT_TRUE(exp.get_right_expression()) << "Right expression is null";

			try
			{
				auto right_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_right_expression());
				EXPECT_EQ(right_int.get_value(), test.expected_integer_value);
			}
			catch (const std::bad_cast &)
			{
				FAIL() << "Right expression is not IntegerLiteral";
			}
		}
		catch (const std::bad_cast &)
		{
			FAIL() << "Statement is not PrefixExpression";
		}
	}
}
