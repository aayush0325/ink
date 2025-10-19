#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <format>

void check_identifier_expression_statements()
{
	std::cout << "Test for identifier expression parsing\n";
	std::cout << "Test starting\n";

	std::string input = "x;";
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
			std::cout << std::format("Failed - got {} statements, expected 1",
									 program->statements.size())
					  << std::endl;
		}

		if (error_count == 0)
		{
			for (const auto &stmt : program->statements)
			{
				try
				{
					ast::ExpressionStatement &exp_stmt = dynamic_cast<ast::ExpressionStatement &>(*stmt);
					ast::Identifier &ident = dynamic_cast<ast::Identifier &>(*exp_stmt.expression);

					if (ident.identifier_name != "x")
					{
						error_count++;
						std::cout << std::format("Failed - Expected identifier name: x, got: {}",
												 ident.identifier_name)
								  << std::endl;
					}

					if (ident.token_literal() != "x")
					{
						error_count++;
						std::cout << std::format("Failed - Expected token literal: x, got: {}",
												 ident.token_literal())
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
	}

	if (error_count == 0)
		std::cout << "Test for identifier expression parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for identifier expression parsing ended ({} errors)\n\n", error_count);
}