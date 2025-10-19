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
	std::cout << "Test for return statement parsing\n";
	std::cout << "Test starting\n";

	std::string input = R"(
		return 5;
		return 10;
		return 993322;
	)";

	auto lexer = std::make_unique<Lexer>(input);
	auto parser = Parser(std::move(lexer));
	auto program = parser.parse_program();
	int error_count = 0;

	if (!program)
	{
		error_count++;
		std::cout << "Failed - parse_program() returned nil\n";
	}

	if (program && error_count == 0)
	{
		if (program->statements.size() != 3)
		{
			error_count++;
			std::cout << std::format("Failed - expected 3 statements, got {}\n",
									 program->statements.size());
		}

		check_parser_errors(parser);

		if (error_count == 0)
		{
			int tc = 1;
			for (const auto &stmt : program->statements)
			{
				if (stmt->token_literal() != "return")
				{
					error_count++;
					std::cout << std::format("Failed - testcase {}: expected return token literal, got '{}'\n",
											 tc, stmt->token_literal());
				}
				else
				{
					try
					{
						auto &return_stmt = dynamic_cast<ast::ReturnStatement &>(*stmt);
						// Test passed for this case
					}
					catch (const std::bad_cast &)
					{
						error_count++;
						std::cout << std::format("Failed - testcase {}: expected ReturnStatement type\n", tc);
					}
				}
				tc++;
			}
		}
	}

	if (error_count == 0)
		std::cout << "Test for return statement parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for return statement parsing ended ({} errors)\n\n", error_count);
}
