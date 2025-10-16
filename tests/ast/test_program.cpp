#include "ast/program.hpp"
#include "ast/let_statement.hpp"
#include "ast/return_statement.hpp"
#include "ast/identifier.hpp"
#include "token/token.hpp"
#include "types/types.hpp"
#include <format>
#include <iostream>
#include <memory>

void test_program_string()
{
	std::cout << "Testing Program string representation...\n";

	auto program = std::make_unique<ast::Program>();

	Token let_token(TokenType::LET, "let");
	Token ident_token(TokenType::IDENT, "myVar");

	auto let_stmt = std::make_unique<ast::LetStatement>(let_token);
	let_stmt->ident = std::make_unique<ast::Identifier>(ident_token, "myVar");

	program->statements.push_back(std::move(let_stmt));

	std::string expected = "let myVar;";
	std::string actual = program->get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_program_string: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_program_string: passed\n";
}

void test_program_multiple_statements()
{
	std::cout << "Testing Program with multiple statements...\n";

	auto program = std::make_unique<ast::Program>();

	Token let_token1(TokenType::LET, "let");
	Token ident_token1(TokenType::IDENT, "x");

	auto let_stmt1 = std::make_unique<ast::LetStatement>(let_token1);
	let_stmt1->ident = std::make_unique<ast::Identifier>(ident_token1, "x");

	Token return_token(TokenType::RETURN, "return");

	auto return_stmt = std::make_unique<ast::ReturnStatement>(return_token);

	program->statements.push_back(std::move(let_stmt1));
	program->statements.push_back(std::move(return_stmt));

	std::string expected = "let x;return ;";
	std::string actual = program->get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_program_multiple_statements: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_program_multiple_statements: passed\n";
}

void test_empty_program()
{
	std::cout << "Testing empty Program...\n";

	auto program = std::make_unique<ast::Program>();

	std::string expected = "";
	std::string actual = program->get_string();

	if (actual != expected)
	{
		std::cout << std::format("test_empty_program: failed - expected '{}', got '{}'\n",
								 expected, actual);
		return;
	}

	std::cout << "test_empty_program: passed\n";
}
