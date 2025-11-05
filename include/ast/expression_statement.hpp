#pragma once

#include "token/token.hpp"
#include "ast/ast.hpp"
#include <memory>

namespace ast
{
	class ExpressionStatement : public Statement
	{
	public:
		virtual std::string token_literal();
		virtual std::string get_string();
		std::unique_ptr<Expression> expression;

		explicit ExpressionStatement(Token token) : token(token) {}

	private:
		Token token;
	};
}