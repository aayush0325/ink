#include "ast/program/program.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <format>
#include <iostream>
#include <memory>
#include <string>

static void test_let_statement(const std::unique_ptr<Statement> &stmt,
							   const std::string &expected_identifier_name,
							   const int &tc)
{
	if (stmt->token_literal() != "let")
	{
		std::cout << std::format("testcase {}: failed - expected let token literal\n", tc);
		return;
	}

	try
	{
		auto &let_stmt = dynamic_cast<LetStatement &>(*stmt);
		if (let_stmt.ident->identifier_name != expected_identifier_name)
		{
			std::cout << std::format("testcase {}: failed - expected identifier name '{}'\n",
									 tc, expected_identifier_name);
			return;
		}
		if (let_stmt.ident->token_literal() != expected_identifier_name)
		{
			std::cout << std::format("testcase {}: failed - expected token literal '{}'\n",
									 tc, expected_identifier_name);
			return;
		}
		std::cout << std::format("testcase {}: passed\n", tc);
	}
	catch (const std::bad_cast &)
	{
		std::cout << std::format("testcase {}: failed - expected LetStatement type\n", tc);
	}
}

void test_let_statement_noexpr()
{
	std::string input = R"(
		let x = 4;
		let y = 123;
		let foobar = 1123;
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

	std::vector<std::string> expected_identifiers = {"x", "y", "foobar"};

	auto expected = expected_identifiers.begin();
	int tc = 1;
	for (const auto &stmt : program->statements)
	{
		test_let_statement(stmt, *expected, tc);
		expected++;
		tc++;
	}
}