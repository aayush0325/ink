#include "ast/return_statement.hpp"

std::string ast::ReturnStatement::token_literal()
{
	return token.literal; // the return token
}

std::string ast::ReturnStatement::get_string()
{
	std::string result = "";
	result += token_literal();
	result += " ";
	while (return_value != nullptr)
		result += return_value->get_string();

	result += ";";
	return result;
}