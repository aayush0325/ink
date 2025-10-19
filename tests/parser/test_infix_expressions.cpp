#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/infix_expression.hpp"
#include "ast/integer_literal.hpp"
#include <format>

void check_infix_expressions()
{
	std::cout << "Test for infix expressions parsing\n";
	std::cout << "Test starting\n";

	struct InfixTest
	{
		std::string input;
		i64 left_value;
		std::string operator_str;
		i64 right_value;
	};

	std::vector<InfixTest> infix_tests = {
		{"5 + 5;", 5, "+", 5},
		{"5 - 5;", 5, "-", 5},
		{"5 * 5;", 5, "*", 5},
		{"5 / 5;", 5, "/", 5},
		{"5 > 5;", 5, ">", 5},
		{"5 < 5;", 5, "<", 5},
		{"5 == 5;", 5, "==", 5},
		{"5 != 5;", 5, "!=", 5}};

	int error_count = 0;

	for (const auto &test : infix_tests)
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
			auto &exp = dynamic_cast<ast::InfixExpression &>(*stmt.expression);

			// Test the left expression (should be an integer literal)
			if (!exp.get_left())
			{
				error_count++;
				std::cout << std::format("Failed - exp.Left is null") << std::endl;
				continue;
			}

			try
			{
				auto left_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_left());
				if (left_int.get_value() != test.left_value)
				{
					error_count++;
					std::cout << std::format("Failed - exp.Left.Value is not {}. got={}",
											 test.left_value, left_int.get_value())
							  << std::endl;
					continue;
				}
			}
			catch (const std::bad_cast &)
			{
				error_count++;
				std::cout << std::format("Failed - exp.Left is not ast.IntegerLiteral. got={}",
										 typeid(*exp.get_left()).name())
						  << std::endl;
				continue;
			}

			// Test the operator
			if (exp.get_operator() != test.operator_str)
			{
				error_count++;
				std::cout << std::format("Failed - exp.Operator is not '{}'. got='{}'",
										 test.operator_str, exp.get_operator())
						  << std::endl;
				continue;
			}

			// Test the right expression (should be an integer literal)
			if (!exp.get_right())
			{
				error_count++;
				std::cout << std::format("Failed - exp.Right is null") << std::endl;
				continue;
			}

			try
			{
				auto right_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_right());
				if (right_int.get_value() != test.right_value)
				{
					error_count++;
					std::cout << std::format("Failed - exp.Right.Value is not {}. got={}",
											 test.right_value, right_int.get_value())
							  << std::endl;
					continue;
				}
			}
			catch (const std::bad_cast &)
			{
				error_count++;
				std::cout << std::format("Failed - exp.Right is not ast.IntegerLiteral. got={}",
										 typeid(*exp.get_right()).name())
						  << std::endl;
				continue;
			}
		}
		catch (const std::bad_cast &)
		{
			error_count++;
			std::cout << std::format("Failed - stmt is not ast.InfixExpression. got={}",
									 typeid(*program->statements[0]).name())
					  << std::endl;
			continue;
		}
	}

	if (error_count == 0)
		std::cout << "Test for infix expressions parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for infix expressions parsing ended ({} errors)\n\n", error_count);
}
