#pragma once

#include "ast/ast.hpp"
#include "ast/identifier.hpp"
#include "token/token.hpp"
#include <memory>

class LetStatement : public Statement
{
public:
	virtual std::string token_literal();
	explicit LetStatement(Token token) : token(token), ident(nullptr), value(nullptr) {}

	std::unique_ptr<Identifier> ident;

private:
	Token token; // the "LET" token
	std::unique_ptr<Expression> value;
};
