#pragma once

#include "token/token.hpp"
#include "ast/ast.hpp"
#include <memory>

namespace ast
{
	// Statements That are just an expression.
	class ExpressionStatement : public Statement
	{
	public:
		virtual std::string token_literal() override;
		virtual std::string get_string() override;
		virtual std::unique_ptr<Node> clone() const override;
		std::unique_ptr<Expression> expression;

		explicit ExpressionStatement(Token token) : token(token) {}

	private:
		Token token;
	};
}