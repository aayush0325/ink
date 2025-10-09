#pragma once

#include "ast/ast.hpp"
#include "ast/identifier/identifier.hpp"
#include "token/token.hpp"
#include <memory>

class LetStatement : public Statement
{
public:
	virtual std::string token_literal();
	explicit LetStatement(Token token) : token(token), ident(), value() {}
	void set_ident(Token token, std::string identifier_name);

private:
	Token token; // the "LET" token
	Identifier ident;
	std::unique_ptr<Expression> value;
};
