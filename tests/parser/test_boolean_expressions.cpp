#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/boolean_literal.hpp"
#include <format>
#include <iostream>

bool test_boolean_literal(ast::Expression *exp, bool expected_value)
{
	try
	{
		ast::BooleanLiteral *boolean_literal = dynamic_cast<ast::BooleanLiteral *>(exp);
		if (!boolean_literal)
		{
			std::cout << std::format("Failed - exp not *ast.BooleanLiteral. got type error\n");
			return false;
		}

		if (boolean_literal->get_value() != expected_value)
		{
			std::cout << std::format("Failed - boolean_literal.Value not {}. got={}\n",
									 expected_value, boolean_literal->get_value());
			return false;
		}

		std::string expected_token = expected_value ? "true" : "false";
		if (boolean_literal->token_literal() != expected_token)
		{
			std::cout << std::format("Failed - boolean_literal.TokenLiteral not {}. got={}\n",
									 expected_token, boolean_literal->token_literal());
			return false;
		}

		return true;
	}
	catch (const std::bad_cast &)
	{
		std::cout << "Failed - dynamic_cast failed for boolean literal\n";
		return false;
	}
}

void check_boolean_literal_statement()
{
	std::cout << "Test for boolean literal expression parsing\n";
	std::cout << "Test starting\n";

	std::string input = "true;";
	auto lexer = std::make_unique<Lexer>(input);
	auto parser = Parser(std::move(lexer));
	auto program = parser.parse_program();
	int error_count = 0;

	if (!program)
	{
		error_count++;
		std::cout << "Failed - Program returned nullptr\n";
	}

	if (program && error_count == 0)
	{
		check_parser_errors(parser);

		if (program->statements.size() != 1)
		{
			error_count++;
			std::cout << std::format("Failed - program has not enough statements. got={}",
									 program->statements.size())
					  << std::endl;
		}

		if (error_count == 0)
		{
			try
			{
				ast::ExpressionStatement &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
				ast::BooleanLiteral &boolean_literal = dynamic_cast<ast::BooleanLiteral &>(*stmt.expression);

				if (boolean_literal.get_value() != true)
				{
					error_count++;
					std::cout << std::format("Failed - literal.Value not {}. got={}", true,
											 boolean_literal.get_value())
							  << std::endl;
				}

				if (boolean_literal.token_literal() != "true")
				{
					error_count++;
					std::cout << std::format("Failed - literal.TokenLiteral not {}. got={}", "true",
											 boolean_literal.token_literal())
							  << std::endl;
				}
			}
			catch (std::bad_cast)
			{
				error_count++;
				std::cout << "Failed - Invalid type returned\n";
			}
		}
	}

	if (error_count == 0)
		std::cout << "Test for boolean literal expression parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for boolean literal expression parsing ended ({} errors)\n\n", error_count);
}

void check_false_boolean_literal_statement()
{
	std::cout << "Test for false boolean literal expression parsing\n";
	std::cout << "Test starting\n";

	std::string input = "false;";
	auto lexer = std::make_unique<Lexer>(input);
	auto parser = Parser(std::move(lexer));
	auto program = parser.parse_program();
	int error_count = 0;

	if (!program)
	{
		error_count++;
		std::cout << "Failed - Program returned nullptr\n";
	}

	if (program && error_count == 0)
	{
		check_parser_errors(parser);

		if (program->statements.size() != 1)
		{
			error_count++;
			std::cout << std::format("Failed - program has not enough statements. got={}",
									 program->statements.size())
					  << std::endl;
		}

		if (error_count == 0)
		{
			try
			{
				ast::ExpressionStatement &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
				ast::BooleanLiteral &boolean_literal = dynamic_cast<ast::BooleanLiteral &>(*stmt.expression);

				if (boolean_literal.get_value() != false)
				{
					error_count++;
					std::cout << std::format("Failed - literal.Value not {}. got={}",
											 false, boolean_literal.get_value())
							  << std::endl;
				}

				if (boolean_literal.token_literal() != "false")
				{
					error_count++;
					std::cout << std::format("Failed - literal.TokenLiteral not {}. got={}", "false",
											 boolean_literal.token_literal())
							  << std::endl;
				}
			}
			catch (std::bad_cast)
			{
				error_count++;
				std::cout << "Failed - Invalid type returned\n";
			}
		}
	}

	if (error_count == 0)
		std::cout << "Test for false boolean literal expression parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for false boolean literal expression parsing ended ({} errors)\n\n", error_count);
}
