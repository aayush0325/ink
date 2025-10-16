#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <format>

void check_identifier_expression_statements()
{
	std::cout << "starting test for identifier expression" << std::endl;
	std::string input = "x;";
	auto lexer = std::make_unique<Lexer>(input);
	auto parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	if (!program)
	{
		std::cout << std::format("Program returned nullptr") << std::endl;
		return;
	}

	check_parser_errors(parser);
	if (program->statements.size() != 1)
	{
		std::cout << std::format("got {} statements, expected 1",
								 program->statements.size())
				  << std::endl;
		return;
	}

	for (const auto &stmt : program->statements)
	{
		try
		{
			ast::ExpressionStatement &exp_stmt = dynamic_cast<ast::ExpressionStatement &>(*stmt);
			ast::Identifier &ident = dynamic_cast<ast::Identifier &>(*exp_stmt.expression);

			if (ident.identifier_name != "x")
			{
				std::cout << std::format("Expected identifier name: x, got: {}",
										 ident.identifier_name)
						  << std::endl;
				return;
			}

			if (ident.token_literal() != "x")
			{
				std::cout << std::format("Expected identifier name: x, got: {}",
										 ident.identifier_name)
						  << std::endl;
				return;
			}

			std::cout << "test for identifier expressions has passed!" << std::endl;
		}
		catch (std::bad_cast)
		{
			std::cout << "invalid type returned" << std::endl;
			return;
		}
	}
}