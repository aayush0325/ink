#include "ast/program.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <gtest/gtest.h>
#include <format>
#include <iostream>
#include <memory>
#include <string>

static void test_let_statement(const std::unique_ptr<ast::Statement> &stmt,
							   const std::string &expected_identifier_name)
{
	EXPECT_EQ(stmt->token_literal(), "let");

	try
	{
		auto &let_stmt = dynamic_cast<ast::LetStatement &>(*stmt);
		EXPECT_EQ(let_stmt.ident->identifier_name, expected_identifier_name);
		EXPECT_EQ(let_stmt.ident->token_literal(), expected_identifier_name);
	}
	catch (const std::bad_cast &)
	{
		FAIL() << "Expected LetStatement type";
	}
}

TEST(ParserTest, LetStatementNoExpr)
{
	std::string input = R"(
		let x = 4;
		let y = 123;
		let foobar = 1123;
	)";

	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_TRUE(program) << "parse_program() returned nil";
	ASSERT_EQ(program->statements.size(), 3);

	check_parser_errors(parser);

	auto expected_identifiers = {"x", "y", "foobar"};

	auto expected = expected_identifiers.begin();
	for (const auto &stmt : program->statements)
	{
		test_let_statement(stmt, *expected);
		expected++;
	}
}