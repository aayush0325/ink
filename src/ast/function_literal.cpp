#include "ast/function_literal.hpp"

std::string ast::FunctionLiteral::get_string()
{
	std::string result = "";
	result += token.literal;
	result += "(";
	for (auto &it : parameters)
	{
		result += it->get_string();
		result += ",";
	}
	result += ")";
	result += body->get_string();
	return result;
}

std::string ast::FunctionLiteral::token_literal()
{
	return token.literal;
}
