#include <iostream>
#include <memory>
#include <string>
#include "tests/parser/test.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/program/program.hpp"
#include "ast/return_statement/return_statement.hpp"
#include "tests/parser/test.hpp"

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
		std::cout << "parse_program() returned nil" << std::endl;
		return;
	}

	if (program->statements.size() != 3)
	{
		std::cout << "incorrect number of statements. expected 3, got: " << program->statements.size() << std::endl;
		return;
	}

	check_parser_errors(parser);

	int tc = 1;
	for (const auto &stmt : program->statements)
	{
		if (stmt->token_literal() != "return")
		{
			std::cout << "testcase: " << tc << " failed, expected return token literal, got: " << stmt->token_literal() << std::endl;
			tc++;
			continue;
		}

		ReturnStatement *rawptr = dynamic_cast<ReturnStatement *>(stmt.get());
		if (!rawptr)
		{
			std::cout << "testcase: " << tc << " failed, expected ReturnStatement pointer" << std::endl;
			tc++;
			continue;
		}

		std::cout << "parse return statements test case: " << tc << " passed" << std::endl;
		tc++;
	}
}
