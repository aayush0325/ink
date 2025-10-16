#include "ast/program.hpp"
#include "ast/return_statement.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <format>
#include <iostream>
#include <memory>
#include <string>

void test_return_statement()
{
	std::string input = R"(
		return 5;
		return 10;
		return 993322;
	)";

	std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
	std::unique_ptr<Program> program = parser.parse_program();

	if (!program)
	{
		std::cout << std::format("error: parse_program() returned nil\n");
		return;
	}

	if (program->statements.size() != 3)
	{
		std::cout << std::format("error: expected 3 statements, got {}\n",
								 program->statements.size());
		return;
	}

	check_parser_errors(parser);

	int tc = 1;
	for (const auto &stmt : program->statements)
	{
		if (stmt->token_literal() != "return")
		{
			std::cout << std::format("testcase {}: failed - expected return token literal, got '{}'\n",
									 tc, stmt->token_literal());
			tc++;
			continue;
		}

		try
		{
			auto &return_stmt = dynamic_cast<ReturnStatement &>(*stmt);
			std::cout << std::format("testcase {}: passed\n", tc);
		}
		catch (const std::bad_cast &)
		{
			std::cout << std::format("testcase {}: failed - expected ReturnStatement type\n", tc);
		}
		tc++;
	}
}
