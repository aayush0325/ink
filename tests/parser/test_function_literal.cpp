#include "tests/parser/test.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "ast/function_literal.hpp"
#include "ast/expression_statement.hpp"
#include "ast/infix_expression.hpp"
#include "ast/identifier.hpp"
#include <format>

void check_function_literal()
{
	std::cout << "Test for function literal parsing\n";
	std::cout << "Test starting\n";

	std::string input = "fn(x, y) { x + y; }";
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
				auto &function = dynamic_cast<ast::FunctionLiteral &>(*stmt.expression);

				// Test parameters - should have 2 parameters: x, y
				if (function.get_parameters().size() != 2)
				{
					error_count++;
					std::cout << std::format("Failed - function literal parameters wrong. want 2, got={}\n",
											 function.get_parameters().size());
				}
				else
				{
					// Test first parameter - should be "x"
					if (function.get_parameters()[0]->identifier_name != "x")
					{
						error_count++;
						std::cout << std::format("Failed - function.Parameters[0] is not 'x'. got='{}'\n",
												 function.get_parameters()[0]->identifier_name);
					}

					// Test second parameter - should be "y"
					if (function.get_parameters()[1]->identifier_name != "y")
					{
						error_count++;
						std::cout << std::format("Failed - function.Parameters[1] is not 'y'. got='{}'\n",
												 function.get_parameters()[1]->identifier_name);
					}
				}

				// Test body - should have 1 statement
				if (!function.get_body())
				{
					error_count++;
					std::cout << "Failed - function.Body is null\n";
				}
				else
				{
					if (function.get_body()->get_statements().size() != 1)
					{
						error_count++;
						std::cout << std::format("Failed - function.Body.Statements has not 1 statements. got={}\n",
												 function.get_body()->get_statements().size());
					}
					else
					{
						auto &body_stmt = dynamic_cast<ast::ExpressionStatement &>(
							*function.get_body()->get_statements()[0]);

						// Test body expression - should be infix expression: x + y
						if (!body_stmt.expression)
						{
							error_count++;
							std::cout << "Failed - bodyStmt.Expression is null\n";
						}
						else
						{
							auto &body_exp = dynamic_cast<ast::InfixExpression &>(*body_stmt.expression);

							// Test left side - should be identifier "x"
							if (!body_exp.get_left())
							{
								error_count++;
								std::cout << "Failed - bodyExp.Left is null\n";
							}
							else
							{
								auto &left_ident = dynamic_cast<ast::Identifier &>(*body_exp.get_left());
								if (left_ident.identifier_name != "x")
								{
									error_count++;
									std::cout << std::format("Failed - bodyExp.Left is not 'x'. got='{}'\n",
															 left_ident.identifier_name);
								}
							}

							// Test operator - should be "+"
							if (body_exp.get_operator() != "+")
							{
								error_count++;
								std::cout << std::format("Failed - bodyExp.Operator is not '+'. got='{}'\n",
														 body_exp.get_operator());
							}

							// Test right side - should be identifier "y"
							if (!body_exp.get_right())
							{
								error_count++;
								std::cout << "Failed - bodyExp.Right is null\n";
							}
							else
							{
								auto &right_ident = dynamic_cast<ast::Identifier &>(*body_exp.get_right());
								if (right_ident.identifier_name != "y")
								{
									error_count++;
									std::cout << std::format("Failed - bodyExp.Right is not 'y'. got='{}'\n",
															 right_ident.identifier_name);
								}
							}
						}
					}
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
		std::cout << "Test for function literal parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for function literal parsing ended ({} errors)\n\n", error_count);
}

void check_function_parameter_parsing()
{
	std::cout << "Test for function parameter parsing\n";
	std::cout << "Test starting\n";

	struct ParameterTest
	{
		std::string input;
		std::vector<std::string> expected_params;
	};

	std::vector<ParameterTest> tests = {
		{"fn() {};", {}},
		{"fn(x) {};", {"x"}},
		{"fn(x, y, z) {};", {"x", "y", "z"}}};

	int error_count = 0;

	for (const auto &test : tests)
	{
		auto lexer = std::make_unique<Lexer>(test.input);
		auto parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		if (!program)
		{
			error_count++;
			std::cout << std::format("Failed - Program returned nullptr for input: {}\n",
									 test.input);
			continue;
		}

		check_parser_errors(parser);

		if (program->statements.size() != 1)
		{
			error_count++;
			std::cout << std::format("Failed - program.Body does not contain {} statements. got={} for input: {}\n",
									 1, program->statements.size(), test.input);
			continue;
		}

		try
		{
			auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
			auto &function = dynamic_cast<ast::FunctionLiteral &>(*stmt.expression);

			if (function.get_parameters().size() != test.expected_params.size())
			{
				error_count++;
				std::cout << std::format("Failed - length parameters wrong. want {}, got={} for input: {}\n",
										 test.expected_params.size(), function.get_parameters().size(), test.input);
				continue;
			}

			for (size_t i = 0; i < test.expected_params.size(); i++)
			{
				if (function.get_parameters()[i]->identifier_name != test.expected_params[i])
				{
					error_count++;
					std::cout << std::format("Failed - function.Parameters[{}] is not '{}'. got='{}' for input: {}\n",
											 i, test.expected_params[i], function.get_parameters()[i]->identifier_name, test.input);
				}
			}
		}
		catch (const std::bad_cast &)
		{
			error_count++;
			std::cout << std::format("Failed - Type cast error for input: {}\n", test.input);
		}
	}

	if (error_count == 0)
		std::cout << "Test for function parameter parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for function parameter parsing ended ({} errors)\n\n", error_count);
}
