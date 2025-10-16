#pragma once

#include "token/token.hpp"
#include "ast/ast.hpp"
#include <memory>

class ExpressionStatement : public Statement
{
public:
	virtual std::string token_literal();
	virtual std::string get_string();

private:
	Token token;
	std::unique_ptr<Expression> expression;
};