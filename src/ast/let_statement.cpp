#include "ast/let_statement.hpp"

std::string LetStatement::token_literal()
{
	return token.literal;
}

std::string LetStatement::get_string()
{
	std::string result = "";
	result += token_literal();
	result += " ";
	result += ident->get_string();
	while (value != nullptr)
		result += value->get_string();
	result += ";";
	return result;
}