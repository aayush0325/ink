#include "tests/parser/test.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "ast/function_literal.hpp"
#include "ast/expression_statement.hpp"
#include "ast/infix_expression.hpp"
#include "ast/identifier.hpp"
#include <gtest/gtest.h>
#include <format>

TEST(ParserTest, FunctionLiteral)
{
	std::string input = "fn(x, y) { x + y; }";
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_TRUE(program) << "Program returned nullptr";
	check_parser_errors(parser);
	ASSERT_EQ(program->statements.size(), 1);

	try
	{
		auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
		auto &function = dynamic_cast<ast::FunctionLiteral &>(*stmt.expression);

		// Test parameters - should have 2 parameters: x, y
		ASSERT_EQ(function.get_parameters().size(), 2);
		EXPECT_EQ(function.get_parameters()[0]->identifier_name, "x");
		EXPECT_EQ(function.get_parameters()[1]->identifier_name, "y");

		// Test body - should have 1 statement
		ASSERT_TRUE(function.get_body()) << "Function body is null";
		ASSERT_EQ(function.get_body()->get_statements().size(), 1);

		auto &body_stmt = dynamic_cast<ast::ExpressionStatement &>(
			*function.get_body()->get_statements()[0]);

		// Test body expression - should be infix expression: x + y
		ASSERT_TRUE(body_stmt.expression) << "Body expression is null";
		auto &body_exp = dynamic_cast<ast::InfixExpression &>(*body_stmt.expression);

		// Test left side - should be identifier "x"
		ASSERT_TRUE(body_exp.get_left()) << "Body expression left is null";
		auto &left_ident = dynamic_cast<ast::Identifier &>(*body_exp.get_left());
		EXPECT_EQ(left_ident.identifier_name, "x");

		// Test operator - should be "+"
		EXPECT_EQ(body_exp.get_operator(), "+");

		// Test right side - should be identifier "y"
		ASSERT_TRUE(body_exp.get_right()) << "Body expression right is null";
		auto &right_ident = dynamic_cast<ast::Identifier &>(*body_exp.get_right());
		EXPECT_EQ(right_ident.identifier_name, "y");
	}
	catch (const std::bad_cast &)
	{
		FAIL() << "Statement is not ExpressionStatement or FunctionLiteral";
	}
}

struct ParameterTest
{
	std::string input;
	std::vector<std::string> expected_params;
};

TEST(ParserTest, FunctionParameters)
{
	std::vector<ParameterTest> tests = {
		{"fn() {};", {}},
		{"fn(x) {};", {"x"}},
		{"fn(x, y, z) {};", {"x", "y", "z"}}};

	for (const auto &test : tests)
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
			auto &function = dynamic_cast<ast::FunctionLiteral &>(*stmt.expression);

			ASSERT_EQ(function.get_parameters().size(), test.expected_params.size());

			for (size_t i = 0; i < test.expected_params.size(); i++)
			{
				EXPECT_EQ(function.get_parameters()[i]->identifier_name, test.expected_params[i]);
			}
		}
		catch (const std::bad_cast &)
		{
			FAIL() << "Type cast error";
		}
	}
}
