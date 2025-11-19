#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include "ast/call_expression.hpp"
#include "ast/infix_expression.hpp"
#include "ast/integer_literal.hpp"
#include "ast/identifier.hpp"
#include <format>

void check_call_expressions()
{
	std::cout << "Test for call expressions parsing\n";
	std::cout << "Test starting\n";

	std::string input = "add(1, 2 * 3, 4 + 5);";
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
			std::cout << std::format("Failed - program.Statements does not contain {} statements. got={}\n",
									 1, program->statements.size())
					  << std::endl;
		}
		else
		{
			try
			{
				auto &stmt = dynamic_cast<ast::ExpressionStatement &>(*program->statements[0]);
				auto &exp = dynamic_cast<ast::CallExpression &>(*stmt.expression);

				// Test function - should be identifier "add"
				if (!exp.get_function())
				{
					error_count++;
					std::cout << "Failed - exp.Function is null\n";
				}
				else
				{
					try
					{
						auto &function = dynamic_cast<ast::Identifier &>(*exp.get_function());
						if (function.identifier_name != "add")
						{
							error_count++;
							std::cout << std::format("Failed - exp.Function is not 'add'. got='{}'\n",
													 function.identifier_name);
						}
					}
					catch (const std::bad_cast &)
					{
						error_count++;
						std::cout << std::format("Failed - exp.Function is not ast.Identifier. got={}\n",
												 typeid(*exp.get_function()).name());
					}
				}

				// Test arguments - should have 3 arguments
				if (exp.get_arguments().size() != 3)
				{
					error_count++;
					std::cout << std::format("Failed - wrong length of arguments. got={}\n",
											 exp.get_arguments().size());
				}
				else
				{
					// Test first argument - should be integer literal 1
					if (!exp.get_arguments()[0])
					{
						error_count++;
						std::cout << "Failed - exp.Arguments[0] is null\n";
					}
					else
					{
						try
						{
							auto &arg1 = dynamic_cast<ast::IntegerLiteral &>(*exp.get_arguments()[0]);
							if (arg1.get_value() != 1)
							{
								error_count++;
								std::cout << std::format("Failed - exp.Arguments[0] is not 1. got={}\n",
														 arg1.get_value());
							}
						}
						catch (const std::bad_cast &)
						{
							error_count++;
							std::cout << std::format("Failed - exp.Arguments[0] is not ast.IntegerLiteral. got={}\n",
													 typeid(*exp.get_arguments()[0]).name());
						}
					}

					// Test second argument - should be infix expression: 2 * 3
					if (!exp.get_arguments()[1])
					{
						error_count++;
						std::cout << "Failed - exp.Arguments[1] is null\n";
					}
					else
					{
						try
						{
							auto &arg2 = dynamic_cast<ast::InfixExpression &>(*exp.get_arguments()[1]);

							// Test left - should be 2
							if (!arg2.get_left())
							{
								error_count++;
								std::cout << "Failed - arg2.Left is null\n";
							}
							else
							{
								try
								{
									auto &left = dynamic_cast<ast::IntegerLiteral &>(*arg2.get_left());
									if (left.get_value() != 2)
									{
										error_count++;
										std::cout << std::format("Failed - arg2.Left is not 2. got={}\n",
																 left.get_value());
									}
								}
								catch (const std::bad_cast &)
								{
									error_count++;
									std::cout << std::format("Failed - arg2.Left is not ast.IntegerLiteral. got={}\n",
															 typeid(*arg2.get_left()).name());
								}
							}

							// Test operator - should be "*"
							if (arg2.get_operator() != "*")
							{
								error_count++;
								std::cout << std::format("Failed - arg2.Operator is not '*'. got='{}'\n",
														 arg2.get_operator());
							}

							// Test right - should be 3
							if (!arg2.get_right())
							{
								error_count++;
								std::cout << "Failed - arg2.Right is null\n";
							}
							else
							{
								try
								{
									auto &right = dynamic_cast<ast::IntegerLiteral &>(*arg2.get_right());
									if (right.get_value() != 3)
									{
										error_count++;
										std::cout << std::format("Failed - arg2.Right is not 3. got={}\n",
																 right.get_value());
									}
								}
								catch (const std::bad_cast &)
								{
									error_count++;
									std::cout << std::format("Failed - arg2.Right is not ast.IntegerLiteral. got={}\n",
															 typeid(*arg2.get_right()).name());
								}
							}
						}
						catch (const std::bad_cast &)
						{
							error_count++;
							std::cout << std::format("Failed - exp.Arguments[1] is not ast.InfixExpression. got={}\n",
													 typeid(*exp.get_arguments()[1]).name());
						}
					}

					// Test third argument - should be infix expression: 4 + 5
					if (!exp.get_arguments()[2])
					{
						error_count++;
						std::cout << "Failed - exp.Arguments[2] is null\n";
					}
					else
					{
						try
						{
							auto &arg3 = dynamic_cast<ast::InfixExpression &>(*exp.get_arguments()[2]);

							// Test left - should be 4
							if (!arg3.get_left())
							{
								error_count++;
								std::cout << "Failed - arg3.Left is null\n";
							}
							else
							{
								try
								{
									auto &left = dynamic_cast<ast::IntegerLiteral &>(*arg3.get_left());
									if (left.get_value() != 4)
									{
										error_count++;
										std::cout << std::format("Failed - arg3.Left is not 4. got={}\n",
																 left.get_value());
									}
								}
								catch (const std::bad_cast &)
								{
									error_count++;
									std::cout << std::format("Failed - arg3.Left is not ast.IntegerLiteral. got={}\n",
															 typeid(*arg3.get_left()).name());
								}
							}

							// Test operator - should be "+"
							if (arg3.get_operator() != "+")
							{
								error_count++;
								std::cout << std::format("Failed - arg3.Operator is not '+'. got='{}'\n",
														 arg3.get_operator());
							}

							// Test right - should be 5
							if (!arg3.get_right())
							{
								error_count++;
								std::cout << "Failed - arg3.Right is null\n";
							}
							else
							{
								try
								{
									auto &right = dynamic_cast<ast::IntegerLiteral &>(*arg3.get_right());
									if (right.get_value() != 5)
									{
										error_count++;
										std::cout << std::format("Failed - arg3.Right is not 5. got={}\n",
																 right.get_value());
									}
								}
								catch (const std::bad_cast &)
								{
									error_count++;
									std::cout << std::format("Failed - arg3.Right is not ast.IntegerLiteral. got={}\n",
															 typeid(*arg3.get_right()).name());
								}
							}
						}
						catch (const std::bad_cast &)
						{
							error_count++;
							std::cout << std::format("Failed - exp.Arguments[2] is not ast.InfixExpression. got={}\n",
													 typeid(*exp.get_arguments()[2]).name());
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
		std::cout << "Test for call expressions parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for call expressions parsing ended ({} errors)\n\n", error_count);
}

