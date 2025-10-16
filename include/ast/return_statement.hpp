#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"
#include <memory>

class ReturnStatement : public Statement
{
	Token token;							  // the return token
	std::unique_ptr<Expression> return_value; // the expression which has to be calculated and returned

	virtual std::string token_literal();
	virtual std::string get_string();

public:
	ReturnStatement(Token token) : token(token), return_value(nullptr) {}
};