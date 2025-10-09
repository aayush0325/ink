#pragma once

#include "token/token.hpp"
#include "ast/ast.hpp"

class Identifier : public Expression
{
public:
	virtual std::string token_literal();
	Identifier(Token token, std::string identifier_name) : token(token), identifier_name(identifier_name) {}
	Identifier() {}

private:
	Token token; // the "IDENT" token
	std::string identifier_name;
};