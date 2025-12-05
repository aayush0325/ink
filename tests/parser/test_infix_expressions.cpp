#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/infix_expression.hpp"
#include "ast/integer_literal.hpp"
#include <gtest/gtest.h>
#include <format>

struct InfixTest
{
	std::string input;
	i64 left_value;
	std::string operator_str;
	i64 right_value;
};

TEST(ParserTest, InfixExpressions)
{
	std::vector<InfixTest> infix_tests = {
		{"5 + 5;", 5, "+", 5},
		{"5 - 5;", 5, "-", 5},
		{"5 * 5;", 5, "*", 5},
		{"5 / 5;", 5, "/", 5},
		{"5 > 5;", 5, ">", 5},
		{"5 < 5;", 5, "<", 5},
		{"5 == 5;", 5, "==", 5},
		{"5 != 5;", 5, "!=", 5}};

	for (const auto &test : infix_tests)
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
			auto &exp = dynamic_cast<ast::InfixExpression &>(*stmt.expression);

			// Test the left expression
			ASSERT_TRUE(exp.get_left()) << "Left expression is null";
			try
			{
				auto left_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_left());
				EXPECT_EQ(left_int.get_value(), test.left_value);
			}
			catch (const std::bad_cast &)
			{
				FAIL() << "Left expression is not IntegerLiteral";
			}

			// Test the operator
			EXPECT_EQ(exp.get_operator(), test.operator_str);

			// Test the right expression
			ASSERT_TRUE(exp.get_right()) << "Right expression is null";
			try
			{
				auto right_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_right());
				EXPECT_EQ(right_int.get_value(), test.right_value);
			}
			catch (const std::bad_cast &)
			{
				FAIL() << "Right expression is not IntegerLiteral";
			}
		}
		catch (const std::bad_cast &)
		{
			FAIL() << "Statement is not InfixExpression";
		}
	}
}
