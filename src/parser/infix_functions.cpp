#include "parser/parser.hpp"

std::unique_ptr<ast::Expression> Parser::infix_parse_infix_expression(std::unique_ptr<ast::Expression> left)
{
	auto infix_expr = std::make_unique<ast::InfixExpression>(current_token, std::move(left), current_token.literal);
	auto precedence = current_precedence();
	next_token();
	infix_expr->set_right(parse_expression(precedence));
	return infix_expr;
}
