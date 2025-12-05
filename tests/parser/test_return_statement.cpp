#include "ast/program.hpp"
#include "ast/return_statement.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <gtest/gtest.h>
#include <format>
#include <iostream>
#include <memory>
#include <string>

TEST(ParserTest, ReturnStatement)
{
	std::string input = R"(
		return 5;
		return 10;
		return 993322;
	)";

	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	ASSERT_TRUE(program) << "parse_program() returned nil";
	ASSERT_EQ(program->statements.size(), 3);

	check_parser_errors(parser);

	for (const auto &stmt : program->statements)
	{
		EXPECT_EQ(stmt->token_literal(), "return");
		
		try
		{
			auto &return_stmt = dynamic_cast<ast::ReturnStatement &>(*stmt);
			(void)return_stmt; // Suppress unused variable warning
		}
		catch (const std::bad_cast &)
		{
			FAIL() << "Expected ReturnStatement type";
		}
	}
}
