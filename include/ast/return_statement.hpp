#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"
#include <memory>

namespace ast
{
	class ReturnStatement : public Statement
{
public:
	ReturnStatement(Token token) : token(token), return_value(nullptr) {}
	virtual std::string token_literal();
	virtual std::string get_string();

private:
	Token token;							  // the return token
	std::unique_ptr<Expression> return_value; // the expression which has to be calculated and returned
};
}