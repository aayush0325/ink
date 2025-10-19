#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/prefix_expression.hpp"
#include "ast/integer_literal.hpp"
#include <format>

void check_prefix_expressions()
{
	std::cout << "Test for prefix expressions parsing\n";
	std::cout << "Test starting\n";

	struct PrefixTest
	{
		std::string input;
		std::string expected_operator;
		i64 expected_integer_value;
	};

	std::vector<PrefixTest> prefix_tests = {
		{"!5;", "!", 5},
		{"-15;", "-", 15}};

	int error_count = 0;

	for (const auto &test : prefix_tests)
	{
		auto lexer = std::make_unique<Lexer>(test.input);
		auto parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		if (!program)
		{
			error_count++;
			std::cout << std::format("Failed - Program returned nullptr for input: {}",
									 test.input)
					  << std::endl;
			continue;
		}

		check_parser_errors(parser);

		if (program->statements.size() != 1)
		{
			error_count++;
			std::cout << std::format("Failed - program.Statements does not contain {} statements. got={}",
									 1, program->statements.size())
					  << std::endl;
			continue;
		}

		try
		{
			auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
			auto &exp = dynamic_cast<ast::PrefixExpression &>(*stmt.expression);

			if (exp.get_prefix_operator() != test.expected_operator)
			{
				error_count++;
				std::cout << std::format("Failed - exp.Operator is not '{}'. got={}",
										 test.expected_operator, exp.get_prefix_operator())
						  << std::endl;
				continue;
			}

			// Test the right expression (should be an integer literal)
			if (!exp.get_right_expression())
			{
				error_count++;
				std::cout << std::format("Failed - exp.Right is null") << std::endl;
				continue;
			}

			try
			{
				auto right_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_right_expression());
				if (right_int.get_value() != test.expected_integer_value)
				{
					error_count++;
					std::cout << std::format("Failed - right.Value is not {}. got={}",
											 test.expected_integer_value, right_int.get_value())
							  << std::endl;
					continue;
				}
			}
			catch (const std::bad_cast &)
			{
				error_count++;
				std::cout << std::format("Failed - exp.Right is not ast.IntegerLiteral. got={}",
										 typeid(*exp.get_right_expression()).name())
						  << std::endl;
				continue;
			}
		}
		catch (const std::bad_cast &)
		{
			error_count++;
			std::cout << std::format("Failed - stmt is not ast.PrefixExpression. got={}",
									 typeid(*program->statements[0]).name())
					  << std::endl;
			continue;
		}
	}

	if (error_count == 0)
		std::cout << "Test for prefix expressions parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for prefix expressions parsing ended ({} errors)\n\n", error_count);
}
