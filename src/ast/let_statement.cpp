#include "ast/let_statement/let_statement.hpp"

std::string LetStatement::token_literal()
{
	return token.literal;
}

void LetStatement::set_ident(Token token, std::string identifier_name)
{
	ident = Identifier(token, identifier_name);
}