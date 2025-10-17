#include "ast/infix_expression.hpp"

std::string ast::InfixExpression::get_string()
{
	std::string result = "";
	result += "(";
	result += left->get_string();
	result += " ";
	result += infix_operator;
	result += " ";
	result += right->get_string();
	result += ")";
	return result;
}

std::string ast::InfixExpression::token_literal()
{
	return infix_token.literal;
}

void ast::InfixExpression::set_right(std::unique_ptr<ast::Expression> right)
{
	this->right = std::move(right);
}