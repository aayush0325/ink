#include "parser/parser.hpp"

/*
	Infix functions are functiosn to parse infix expressions.

	Infix expressions are the expression that take two expressions to the left
	and right of it and the operator in between is called the infix operator.
	The basic flow of parsing an infix expression is to take the LEFT as an
	input param (comes from the ongoing parse_expression() call) and then call
	it again with the precedence of the current token
*/

std::unique_ptr<ast::Expression> Parser::infix_parse_infix_expression(
	std::unique_ptr<ast::Expression> left)
{
	auto infix_expr = std::make_unique<ast::InfixExpression>(
		current_token, std::move(left), current_token.literal);

	auto precedence = current_precedence();
	next_token();
	infix_expr->set_right(parse_expression(precedence));
	return infix_expr;
}

std::unique_ptr<ast::Expression> Parser::infix_parse_call_expression(
	std::unique_ptr<ast::Expression> left)
{
	auto exp = std::make_unique<ast::CallExpression>(current_token);
	exp->set_function(std::move(left));
	exp->set_arguments(std::move(parse_call_arguments()));
	return exp;
}
