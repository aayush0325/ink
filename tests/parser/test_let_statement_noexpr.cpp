#include <iostream>
#include <memory>
#include <string>
#include "tests/parser/test.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/program/program.hpp"

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
		std::cout << "parse_program() returned nil" << std::endl;
		return;
	}

	if (program->statements.size() != 3)
	{
		std::cout << "incorrect number of statements pushed into the statements vector by the parser: " << program->statements.size() << std::endl;
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

static void test_let_statement(const std::unique_ptr<Statement> &stmt, const std::string &expected_identifier_name, const int &tc)
{
	if (stmt->token_literal() != "let")
	{
		std::cout << "testcase: " << tc << " failed, expected let token literal" << std::endl;
		return;
	}

	LetStatement *rawptr = dynamic_cast<LetStatement *>(stmt.get());
	if (!rawptr)
	{
		std::cout << "testcase: " << tc << " failed, expected LetStatement pointer" << std::endl;
		return;
	}
	if (rawptr->ident->identifier_name != expected_identifier_name)
	{
		std::cout << "testcase: " << tc << " failed, expected name: " << expected_identifier_name << std::endl;
		return;
	}
	if (rawptr->ident->token_literal() != expected_identifier_name)
	{
		std::cout << "testcase: " << tc << " failed, expected token literal: " << expected_identifier_name << std::endl;
		return;
	}
	std::cout << "parse let statements without expression test case: " << tc << " passed" << std::endl;
}

static void check_parser_errors(Parser &parser)
{
	if (parser.get_errors().size() == 0)
		return;
	std::cout << "the parser has: " << parser.get_errors().size() << " errors" << std::endl;
	for (auto &it : parser.get_errors())
		std::cout << it << std::endl;
}