#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	class PrefixExpression : public Expression
{
	Token token;
	std::string prefix_operator;
	std::unique_ptr<Expression> right_expression;

public:
	std::string get_string();
	std::string token_literal();
};
}