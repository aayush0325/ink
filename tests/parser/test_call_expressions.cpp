#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/call_expression.hpp"
#include "ast/infix_expression.hpp"
#include "ast/integer_literal.hpp"
#include "ast/identifier.hpp"
#include <format>
#include <gtest/gtest.h>

TEST(ParserTest, CallExpressions)
{
	std::string input = "add(1, 2 * 3, 4 + 5);";
	auto lexer = std::make_unique<Lexer>(input);
	auto parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_NE(program, nullptr) << "parse_program() returned nullptr";
	check_parser_errors(parser);

	ASSERT_EQ(program->statements.size(), 1)
		<< "expected 1 statement, got: " << program->statements.size();

	// Get expression statement
	auto *stmt = dynamic_cast<ast::ExpressionStatement *>(program->statements[0].get());
	ASSERT_NE(stmt, nullptr) << "program.statements[0] is not ast::ExpressionStatement";

	// Get call expression
	auto *call = dynamic_cast<ast::CallExpression *>(stmt->expression.get());
	ASSERT_NE(call, nullptr) << "statement expression is not ast::CallExpression";
	ASSERT_NE(call->get_function(), nullptr) << "call.get_function() returned nullptr";

	// Function should be identifier "add"
	auto *fn_ident = dynamic_cast<ast::Identifier *>(call->get_function().get());
	ASSERT_NE(fn_ident, nullptr) << "call function is not ast::Identifier";
	EXPECT_EQ(fn_ident->identifier_name, "add");

	// Arguments length
	auto &args = call->get_arguments();
	ASSERT_EQ(args.size(), 3) << "wrong number of arguments";

	// Arg 0 -> IntegerLiteral 1
	{
		auto *arg0 = dynamic_cast<ast::IntegerLiteral *>(args[0].get());
		ASSERT_NE(arg0, nullptr) << "arg0 is not ast::IntegerLiteral";
		EXPECT_EQ(arg0->get_value(), 1);
	}

	// Arg 1 -> InfixExpression (2 * 3)
	{
		auto *arg1 = dynamic_cast<ast::InfixExpression *>(args[1].get());
		ASSERT_NE(arg1, nullptr) << "arg1 is not ast::InfixExpression";

		auto *left = dynamic_cast<ast::IntegerLiteral *>(arg1->get_left().get());

		ASSERT_NE(left, nullptr) << "arg1.left is not ast::IntegerLiteral";
		EXPECT_EQ(left->get_value(), 2);
		EXPECT_EQ(arg1->get_operator(), "*");

		auto *right = dynamic_cast<ast::IntegerLiteral *>(arg1->get_right().get());
		ASSERT_NE(right, nullptr) << "arg1.right is not ast::IntegerLiteral";
		EXPECT_EQ(right->get_value(), 3);
	}

	// Arg 2 -> InfixExpression (4 + 5)
	{
		auto *arg2 = dynamic_cast<ast::InfixExpression *>(args[2].get());
		ASSERT_NE(arg2, nullptr) << "arg2 is not ast::InfixExpression";

		auto *left = dynamic_cast<ast::IntegerLiteral *>(arg2->get_left().get());
		ASSERT_NE(left, nullptr) << "arg2.left is not ast::IntegerLiteral";
		EXPECT_EQ(left->get_value(), 4);

		EXPECT_EQ(arg2->get_operator(), "+");

		auto *right = dynamic_cast<ast::IntegerLiteral *>(arg2->get_right().get());
		ASSERT_NE(right, nullptr) << "arg2.right is not ast::IntegerLiteral";
		EXPECT_EQ(right->get_value(), 5);
	}
}
