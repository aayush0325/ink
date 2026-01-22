#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	// Type of expressions that just need one value, like let x = !false;
	class PrefixExpression : public Expression
	{
		Token token;
		std::string prefix_operator;
		std::unique_ptr<Expression> right_expression;

	public:
		virtual std::string get_string() override;
		virtual std::string token_literal() override;
		virtual std::unique_ptr<Node> clone() const override;
		void set_right_expression(std::unique_ptr<ast::Expression> expr);

		// Getter methods for testing
		const std::string &get_prefix_operator() const { return prefix_operator; }
		const std::unique_ptr<Expression> &get_right_expression() const { return right_expression; }

		explicit PrefixExpression(Token token, std::string prefix_operator);
	};
}