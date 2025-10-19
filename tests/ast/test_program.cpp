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
	std::cout << "Test for program string representation\n";
	std::cout << "Test starting\n";

	auto program = std::make_unique<ast::Program>();

	Token let_token(TokenType::LET, "let");
	Token ident_token(TokenType::IDENT, "myVar");

	auto let_stmt = std::make_unique<ast::LetStatement>(let_token);
	let_stmt->ident = std::make_unique<ast::Identifier>(ident_token, "myVar");

	program->statements.push_back(std::move(let_stmt));

	std::string expected = "let myVar;";
	std::string actual = program->get_string();
	int error_count = 0;

	if (actual != expected)
	{
		error_count++;
		std::cout << std::format("Failed - expected '{}', got '{}'\n",
								 expected, actual);
	}

	if (error_count == 0)
		std::cout << "Test for program string representation ended (all passed)\n";
	else
		std::cout << std::format("Test for program string representation ended ({} errors)\n", error_count);
}

void test_program_multiple_statements()
{
	std::cout << "Test for program multiple statements representation\n";
	std::cout << "Test starting\n";

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
	int error_count = 0;

	if (actual != expected)
	{
		error_count++;
		std::cout << std::format("Failed - expected '{}', got '{}'\n",
								 expected, actual);
	}

	if (error_count == 0)
		std::cout << "Test for program multiple statements representation ended (all passed)\n";
	else
		std::cout << std::format("Test for program multiple statements representation ended ({} errors)\n", error_count);
}

void test_empty_program()
{
	std::cout << "Test for empty program representation\n";
	std::cout << "Test starting\n";

	auto program = std::make_unique<ast::Program>();

	std::string expected = "";
	std::string actual = program->get_string();
	int error_count = 0;

	if (actual != expected)
	{
		error_count++;
		std::cout << std::format("Failed - expected '{}', got '{}'\n",
								 expected, actual);
	}

	if (error_count == 0)
		std::cout << "Test for empty program representation ended (all passed)\n\n";
	else
		std::cout << std::format("Test for empty program representation ended ({} errors)\n\n", error_count);
}
