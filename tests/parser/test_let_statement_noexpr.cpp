#include "ast/program.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <format>
#include <iostream>
#include <memory>
#include <string>

static bool test_let_statement(const std::unique_ptr<ast::Statement> &stmt,
							   const std::string &expected_identifier_name,
							   const int &tc)
{
	if (stmt->token_literal() != "let")
	{
		std::cout << std::format("Failed - testcase {}: expected let token literal\n", tc);
		return false;
	}

	try
	{
		auto &let_stmt = dynamic_cast<ast::LetStatement &>(*stmt);
		if (let_stmt.ident->identifier_name != expected_identifier_name)
		{
			std::cout << std::format("Failed - testcase {}: expected identifier name '{}'\n",
									 tc, expected_identifier_name);
			return false;
		}
		if (let_stmt.ident->token_literal() != expected_identifier_name)
		{
			std::cout << std::format("Failed - testcase {}: expected token literal '{}'\n",
									 tc, expected_identifier_name);
			return false;
		}
		return true;
	}
	catch (const std::bad_cast &)
	{
		std::cout << std::format("Failed - testcase {}: expected LetStatement type\n", tc);
		return false;
	}
}

void test_let_statement_noexpr()
{
	std::cout << "Test for let statement parsing without expressions\n";
	std::cout << "Test starting\n";

	std::string input = R"(
		let x = 4;
		let y = 123;
		let foobar = 1123;
	)";

	auto lexer = std::make_unique<Lexer>(input);
	Parser parser = Parser(std::move(lexer));
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
			auto expected_identifiers = {"x", "y", "foobar"};

			auto expected = expected_identifiers.begin();
			int tc = 1;
			for (const auto &stmt : program->statements)
			{
				if (!test_let_statement(stmt, *expected, tc))
				{
					error_count++;
				}
				expected++;
				tc++;
			}
		}
	}

	if (error_count == 0)
		std::cout << "Test for let statement parsing without expressions ended (all passed)\n\n";
	else
		std::cout << std::format("Test for let statement parsing without expressions ended ({} errors)\n\n", error_count);
}