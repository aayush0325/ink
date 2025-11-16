#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/if_expression.hpp"
#include "ast/infix_expression.hpp"
#include "ast/identifier.hpp"
#include <format>

void check_if_expressions()
{
	std::cout << "Test for if expressions parsing\n";
	std::cout << "Test starting\n";

	std::string input = "if (x < y) { x }";
	auto lexer = std::make_unique<Lexer>(input);
	auto parser = Parser(std::move(lexer));
	auto program = parser.parse_program();

	int error_count = 0;

	if (!program)
	{
		error_count++;
		std::cout << "Failed - Program returned nullptr\n";
	}
	else
	{
		check_parser_errors(parser);

		if (program->statements.size() != 1)
		{
			error_count++;
			std::cout << std::format("Failed - program.Body does not contain {} statements. got={}\n",
									 1, program->statements.size())
					  << std::endl;
		}
		else
		{
			try
			{
				auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
				auto &exp = dynamic_cast<ast::IfExpression &>(*stmt.expression);

				// Test condition - should be an infix expression: x < y
				if (!exp.get_condition())
				{
					error_count++;
					std::cout << "Failed - exp.Condition is null\n";
				}
				else
				{
					auto &condition = dynamic_cast<ast::InfixExpression &>(*exp.get_condition());

					// Test left side - should be identifier "x"
					if (!condition.get_left())
					{
						error_count++;
						std::cout << "Failed - condition.Left is null\n";
					}
					else
					{
						auto &left_ident = dynamic_cast<ast::Identifier &>(*condition.get_left());
						if (left_ident.identifier_name != "x")
						{
							error_count++;
							std::cout << std::format("Failed - condition.Left is not 'x'. got='{}'\n",
													 left_ident.identifier_name);
						}
					}

					// Test operator - should be "<"
					if (condition.get_operator() != "<")
					{
						error_count++;
						std::cout << std::format("Failed - condition.Operator is not '<'. got='{}'\n",
												 condition.get_operator());
					}

					// Test right side - should be identifier "y"
					if (!condition.get_right())
					{
						error_count++;
						std::cout << "Failed - condition.Right is null\n";
					}
					else
					{
						auto &right_ident = dynamic_cast<ast::Identifier &>(*condition.get_right());
						if (right_ident.identifier_name != "y")
						{
							error_count++;
							std::cout << std::format("Failed - condition.Right is not 'y'. got='{}'\n",
													 right_ident.identifier_name);
						}
					}
				}

				// Test consequence - should have 1 statement
				if (!exp.get_consequence())
				{
					error_count++;
					std::cout << "Failed - exp.Consequence is null\n";
				}
				else
				{
					if (exp.get_consequence()->get_statements().size() != 1)
					{
						error_count++;
						std::cout << std::format("Failed - consequence is not 1 statements. got={}\n",
												 exp.get_consequence()->get_statements().size());
					}
					else
					{
						auto &consequence = dynamic_cast<ast::ExpressionStatement &>(
							*exp.get_consequence()->get_statements()[0]);

						// Test consequence expression - should be identifier "x"
						if (!consequence.expression)
						{
							error_count++;
							std::cout << "Failed - consequence.Expression is null\n";
						}
						else
						{
							auto &consequence_ident = dynamic_cast<ast::Identifier &>(*consequence.expression);
							if (consequence_ident.identifier_name != "x")
							{
								error_count++;
								std::cout << std::format("Failed - consequence.Expression is not 'x'. got='{}'\n",
														 consequence_ident.identifier_name);
							}
						}
					}
				}

				// Test alternative - should be nil (nullptr)
				if (exp.get_alternative() != nullptr)
				{
					error_count++;
					std::cout << "Failed - exp.Alternative.Statements was not nil. got not null\n";
				}
			}
			catch (const std::bad_cast &)
			{
				error_count++;
				std::cout << std::format("Failed - program.Statements[0] is not ast.ExpressionStatement. got={}\n",
										 typeid(*program->statements[0]).name());
			}
		}
	}

	if (error_count == 0)
		std::cout << "Test for if expressions parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for if expressions parsing ended ({} errors)\n\n", error_count);
}
