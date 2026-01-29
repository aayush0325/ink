#include <gtest/gtest.h>
#include "parser/parser.hpp"
#include "ast/string_literal.hpp"
#include "lexer/lexer.hpp"

TEST(ParserTest, TestStringLiteralExpression)
{
	std::string input = R"("hello world";)";
	auto l = std::make_unique<Lexer>(input);
	Parser p(std::move(l));
	auto program = p.parse_program();

	ASSERT_EQ(p.get_errors().size(), 0);
	ASSERT_EQ(program->statements.size(), 1);

	auto stmt = dynamic_cast<ast::ExpressionStatement *>(program->statements[0].get());
	ASSERT_NE(stmt, nullptr);

	auto literal = dynamic_cast<ast::StringLiteral *>(stmt->expression.get());
	ASSERT_NE(literal, nullptr);

	EXPECT_EQ(literal->get_value(), "hello world");
}
