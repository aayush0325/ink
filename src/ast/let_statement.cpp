#include "ast/let_statement.hpp"

std::string ast::LetStatement::token_literal()
{
	return token.literal;
}

std::string ast::LetStatement::get_string()
{
	std::string result = "";
	result += token_literal();
	result += " ";
	result += ident->get_string();
	if (value != nullptr)
	{
		result += " = ";
		result += value->get_string();
	}
	result += ";";
	return result;
}

void ast::LetStatement::set_value(std::unique_ptr<ast::Expression> expr)
{
	value = std::move(expr);
}
