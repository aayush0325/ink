#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/infix_expression.hpp"
#include "ast/integer_literal.hpp"
#include <format>

void check_infix_expressions()
{
	std::cout << "starting test for infix expressions" << std::endl;

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

	for (const auto &test : infix_tests)
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
			auto &exp = dynamic_cast<ast::InfixExpression &>(*stmt.expression);

			// Test the left expression (should be an integer literal)
			if (!exp.get_left())
			{
				std::cout << std::format("exp.Left is null") << std::endl;
				return;
			}

			try
			{
				auto left_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_left());
				if (left_int.get_value() != test.left_value)
				{
					std::cout << std::format("exp.Left.Value is not {}. got={}",
											 test.left_value, left_int.get_value())
							  << std::endl;
					return;
				}
			}
			catch (const std::bad_cast &)
			{
				std::cout << std::format("exp.Left is not ast.IntegerLiteral. got={}",
										 typeid(*exp.get_left()).name())
						  << std::endl;
				return;
			}

			// Test the operator
			if (exp.get_operator() != test.operator_str)
			{
				std::cout << std::format("exp.Operator is not '{}'. got='{}'",
										 test.operator_str, exp.get_operator())
						  << std::endl;
				return;
			}

			// Test the right expression (should be an integer literal)
			if (!exp.get_right())
			{
				std::cout << std::format("exp.Right is null") << std::endl;
				return;
			}

			try
			{
				auto right_int = dynamic_cast<ast::IntegerLiteral &>(*exp.get_right());
				if (right_int.get_value() != test.right_value)
				{
					std::cout << std::format("exp.Right.Value is not {}. got={}",
											 test.right_value, right_int.get_value())
							  << std::endl;
					return;
				}
			}
			catch (const std::bad_cast &)
			{
				std::cout << std::format("exp.Right is not ast.IntegerLiteral. got={}",
										 typeid(*exp.get_right()).name())
						  << std::endl;
				return;
			}
		}
		catch (const std::bad_cast &)
		{
			std::cout << std::format("stmt is not ast.InfixExpression. got={}",
									 typeid(*program->statements[0]).name())
					  << std::endl;
			return;
		}
	}

	std::cout << "test for infix expressions has passed!" << std::endl;
}
