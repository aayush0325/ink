#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/if_expression.hpp"
#include "ast/infix_expression.hpp"
#include "ast/identifier.hpp"
#include <gtest/gtest.h>
#include <format>

TEST(ParserTest, IfExpression)
{
	std::string input = "if (x < y) { x }";
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_TRUE(program) << "Program returned nullptr";
	check_parser_errors(parser);
	ASSERT_EQ(program->statements.size(), 1);

	try
	{
		auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
		auto &exp = dynamic_cast<ast::IfExpression &>(*stmt.expression);

		// Test condition - should be an infix expression: x < y
		ASSERT_TRUE(exp.get_condition()) << "Condition is null";
		try
		{
			auto &condition = dynamic_cast<ast::InfixExpression &>(*exp.get_condition());

			// Test left side - should be identifier "x"
			ASSERT_TRUE(condition.get_left()) << "Condition left is null";
			auto &left_ident = dynamic_cast<ast::Identifier &>(*condition.get_left());
			EXPECT_EQ(left_ident.identifier_name, "x");

			// Test operator - should be "<"
			EXPECT_EQ(condition.get_operator(), "<");

			// Test right side - should be identifier "y"
			ASSERT_TRUE(condition.get_right()) << "Condition right is null";
			auto &right_ident = dynamic_cast<ast::Identifier &>(*condition.get_right());
			EXPECT_EQ(right_ident.identifier_name, "y");
		}
		catch (const std::bad_cast &)
		{
			FAIL() << "Condition is not InfixExpression";
		}

		// Test consequence - should have 1 statement
		ASSERT_TRUE(exp.get_consequence()) << "Consequence is null";
		ASSERT_EQ(exp.get_consequence()->get_statements().size(), 1);

		auto &consequence = dynamic_cast<ast::ExpressionStatement &>(
			*exp.get_consequence()->get_statements()[0]);

		// Test consequence expression - should be identifier "x"
		ASSERT_TRUE(consequence.expression) << "Consequence expression is null";
		auto &consequence_ident = dynamic_cast<ast::Identifier &>(*consequence.expression);
		EXPECT_EQ(consequence_ident.identifier_name, "x");

		// Test alternative - should be nil (nullptr)
		EXPECT_EQ(exp.get_alternative(), nullptr);
	}
	catch (const std::bad_cast &)
	{
		FAIL() << "Statement is not ExpressionStatement or IfExpression";
	}
}
