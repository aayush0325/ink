#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <gtest/gtest.h>
#include <format>

TEST(ParserTest, IntegerLiteralExpression)
{
	std::string input = "5;";
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_TRUE(program) << "Program returned nullptr";
	check_parser_errors(parser);
	ASSERT_EQ(program->statements.size(), 1);

	try
	{
		ast::ExpressionStatement &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
		ast::IntegerLiteral &integer_literal = dynamic_cast<ast::IntegerLiteral &>(*stmt.expression);

		EXPECT_EQ(integer_literal.get_value(), 5);
		EXPECT_EQ(integer_literal.token_literal(), "5");
	}
	catch (std::bad_cast)
	{
		FAIL() << "Invalid type returned";
	}
}
