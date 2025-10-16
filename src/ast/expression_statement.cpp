#include "ast/expression_statement.hpp"

std::string ExpressionStatement::token_literal()
{
	return token.literal;
}

std::string ExpressionStatement::get_string()
{
	std::string result = "";
	while (expression != nullptr)
		result += expression->get_string();
	return result;
}