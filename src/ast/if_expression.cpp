#include "ast/if_expression.hpp"

std::string ast::IfExpression::get_string()
{
	std::string result = "";
	result += "if";
	result += condition->get_string();
	result += " ";
	result += consequence->get_string();
	if (alternative != nullptr)
	{
		result += "else";
		result += alternative->get_string();
	}
	return result;
}

std::string ast::IfExpression::token_literal()
{
	return token.literal;
}

void ast::IfExpression::set_condition(std::unique_ptr<Expression> expr)
{
	condition = std::move(expr);
}

void ast::IfExpression::set_consequence(std::unique_ptr<BlockStatement> expr)
{
	consequence = std::move(expr);
}

void ast::IfExpression::set_alternative(std::unique_ptr<BlockStatement> expr)
{
	alternative = std::move(expr);
}