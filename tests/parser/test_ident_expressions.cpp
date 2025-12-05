#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <gtest/gtest.h>
#include <format>

TEST(ParserTest, IdentifierExpression)
{
	std::string input = "x;";
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_TRUE(program) << "Program returned nullptr";
	check_parser_errors(parser);
	ASSERT_EQ(program->statements.size(), 1);

	try
	{
		ast::ExpressionStatement &exp_stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
		ast::Identifier &ident = dynamic_cast<ast::Identifier &>(*exp_stmt.expression);

		EXPECT_EQ(ident.identifier_name, "x");
		EXPECT_EQ(ident.token_literal(), "x");
	}
	catch (std::bad_cast)
	{
		FAIL() << "Invalid type returned";
	}
}