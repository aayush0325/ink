#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/prefix_expression.hpp"
#include "ast/integer_literal.hpp"
#include <format>

void check_prefix_expressions()
{
	std::cout << "starting test for prefix expressions" << std::endl;

	struct PrefixTest
	{
		std::string input;
		std::string expected_operator;
		i64 expected_integer_value;
	};

	std::vector<PrefixTest> prefix_tests = {
		{"!5;", "!", 5},
		{"-15;", "-", 15}};

	for (const auto &test : prefix_tests)
	{
		auto lexer = std::make_unique<Lexer>(test.input);
		auto parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		if (!program)
		{
			std::cout << std::format("Program returned nullptr for input: {}",
									 test.input)
					  << std::endl;
			return;
		}

		check_parser_errors(parser);

		if (program->statements.size() != 1)
		{
			std::cout << std::format("program.Statements does not contain {} statements. got={}",
									 1, program->statements.size())
					  << std::endl;
			return;
		}

		try
		{
			auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
			auto &exp = dynamic_cast<ast::PrefixExpression &>(*stmt.expression);

			if (exp.get_prefix_operator() != test.expected_operator)
			{
				std::cout << std::format("exp.Operator is not '{}'. got={}",
										 test.expected_operator, exp.get_prefix_operator())
						  << std::endl;
				return;
			}

			// Test the right expression (should be an integer literal)
			if (!exp.get_right_expression())
			{
				std::cout << std::format("exp.Right is null") << std::endl;
				return;
			}

			try
			{
				auto right_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_right_expression());
				if (right_int.get_value() != test.expected_integer_value)
				{
					std::cout << std::format("right.Value is not {}. got={}",
											 test.expected_integer_value, right_int.get_value())
							  << std::endl;
					return;
				}
			}
			catch (const std::bad_cast &)
			{
				std::cout << std::format("exp.Right is not ast.IntegerLiteral. got={}",
										 typeid(*exp.get_right_expression()).name())
						  << std::endl;
				return;
			}
		}
		catch (const std::bad_cast &)
		{
			std::cout << std::format("stmt is not ast.PrefixExpression. got={}",
									 typeid(*program->statements[0]).name())
					  << std::endl;
			return;
		}
	}

	std::cout << "test for prefix expressions has passed!" << std::endl;
}
