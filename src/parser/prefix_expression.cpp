#include "ast/prefix_expression.hpp"

std::string ast::PrefixExpression::get_string()
{
	std::string result = "";
	result += "(";
	result += prefix_operator;
	result += right_expression->get_string();
	result += ")";
	return result;
}

std::string ast::PrefixExpression::token_literal()
{
	return token.literal;
}

ast::PrefixExpression::PrefixExpression(Token token, std::string prefix_operator)
	: token(token), prefix_operator(prefix_operator), right_expression(nullptr) {}

void ast::PrefixExpression::set_right_expression(std::unique_ptr<ast::Expression> expr)
{
	right_expression = std::move(expr);
}