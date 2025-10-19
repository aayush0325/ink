#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <format>

void check_integer_literal_statement()
{
	std::cout << "Test for integer literal expression parsing\n";
	std::cout << "Test starting\n";

	std::string input = "5;";
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
				ast::IntegerLiteral &integer_literal = dynamic_cast<ast::IntegerLiteral &>(*stmt.expression);

				if (integer_literal.get_value() != 5)
				{
					error_count++;
					std::cout << std::format("Failed - literal.Value not {}. got={}", 5, integer_literal.get_value()) << std::endl;
				}

				if (integer_literal.token_literal() != "5")
				{
					error_count++;
					std::cout << std::format("Failed - literal.TokenLiteral not {}. got={}", "5", integer_literal.token_literal()) << std::endl;
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
		std::cout << "Test for integer literal expression parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for integer literal expression parsing ended ({} errors)\n\n", error_count);
}