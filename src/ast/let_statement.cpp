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

std::unique_ptr<ast::Node> ast::LetStatement::clone() const
{
	auto clone = std::make_unique<LetStatement>(token);
	if (ident)
	{
		auto ident_clone = ident->clone();
		clone->ident = std::unique_ptr<Identifier>(static_cast<Identifier *>(
			ident_clone.release()));
	}
	if (value)
	{
		auto val_clone = value->clone();
		clone->set_value(std::unique_ptr<Expression>(static_cast<Expression *>(
			val_clone.release())));
	}
	return clone;
}
