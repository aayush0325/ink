#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <format>

void check_integer_literal_statement()
{
	std::cout << "starting test for integer literal expression" << std::endl;
	std::string input = "5;";
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
		std::cout << std::format("program has not enough statements. got={}", program->statements.size()) << std::endl;
		return;
	}

	try
	{
		ExpressionStatement &stmt = dynamic_cast<ExpressionStatement &>(*program->statements[0]);
		IntegerLiteral &integer_literal = dynamic_cast<IntegerLiteral &>(*stmt.expression);

		if (integer_literal.get_value() != 5)
		{
			std::cout << std::format("literal.Value not {}. got={}", 5, integer_literal.get_value()) << std::endl;
			return;
		}
		
		if (integer_literal.token_literal() != "5")
		{
			std::cout << std::format("literal.TokenLiteral not {}. got={}", "5", integer_literal.token_literal()) << std::endl;
			return;
		}
		
		std::cout << "test for integer literal expressions has passed!" << std::endl;
	}
	catch (std::bad_cast)
	{
		std::cout << "Invalid type returned" << std::endl;
		return;
	}
}