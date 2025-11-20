#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/boolean_literal.hpp"
#include <format>
#include <iostream>
#include <gtest/gtest.h>

TEST(ParserTest, BooleanExpressions)
{
	std::vector<std::string> inputs = {
		"true;",
		"false;",
	};

	std::vector<bool> expected_values = {
		true,
		false,
	};

	for (size_t i = 0; i < inputs.size(); i++)
	{
		auto lexer = std::make_unique<Lexer>(inputs[i]);
		Parser parser(std::move(lexer));
		auto program = parser.parse_program();

		ASSERT_NE(program, nullptr) << "Program returned nullptr";
		check_parser_errors(parser);

		ASSERT_EQ(program->statements.size(), 1)
			<< "Program should have exactly 1 statement";

		auto *stmt = dynamic_cast<ast::ExpressionStatement *>(program->statements[0].get());
		ASSERT_NE(stmt, nullptr) << "Statement is not an ExpressionStatement";

		auto *bool_lit = dynamic_cast<ast::BooleanLiteral *>(stmt->expression.get());
		ASSERT_NE(bool_lit, nullptr) << "Expression is not a BooleanLiteral";

		// Compare expected boolean value
		EXPECT_EQ(bool_lit->get_value(), expected_values[i]);

		// Compare token literal
		EXPECT_EQ(bool_lit->token_literal(), (expected_values[i] ? "true" : "false"));

		// If == is implemented, assert against a constructed literal
		Token tok(expected_values[i] ? TokenType::TRUE : TokenType::FALSE,
				  expected_values[i] ? "true" : "false");

		ast::BooleanLiteral expected_bool(tok);
		EXPECT_EQ(*bool_lit, expected_bool);
	}
}
