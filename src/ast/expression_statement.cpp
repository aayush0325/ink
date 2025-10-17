#include "ast/expression_statement.hpp"

std::string ast::ExpressionStatement::token_literal()
{
	return token.literal;
}

std::string ast::ExpressionStatement::get_string()
{
	std::string result = "";
	if (expression != nullptr)
		result += expression->get_string();
	return result;
}