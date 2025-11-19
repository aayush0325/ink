#include "ast/call_expression.hpp"
#include <sstream>

std::string ast::CallExpression::get_string()
{
	std::stringstream ss;
	ss << function->get_string();
	ss << "(";

	for (size_t i = 0; i < arguments.size(); i++)
	{
		ss << arguments[i]->get_string();
		if (i < arguments.size() - 1)
		{
			ss << ", ";
		}
	}

	ss << ")";
	return ss.str();
}

std::string ast::CallExpression::token_literal()
{
	return token.literal;
}
