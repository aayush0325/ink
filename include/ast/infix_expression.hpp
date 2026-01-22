#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	// Type of expression that takes a left and right to an operator like  1 + 2
	class InfixExpression : public Expression
	{
	public:
		virtual std::string get_string() override;
		virtual std::string token_literal() override;
		virtual std::unique_ptr<Node> clone() const override;

		explicit InfixExpression(Token infix_token, std::unique_ptr<Expression> left, std::string infix_operator)
			: infix_token(infix_token), left(std::move(left)), right(nullptr), infix_operator(infix_operator) {}

		void set_right(std::unique_ptr<Expression> right);

		// Getter methods for testing
		const std::unique_ptr<Expression> &get_left() const { return left; }
		const std::unique_ptr<Expression> &get_right() const { return right; }
		const std::string &get_operator() const { return infix_operator; }

	private:
		Token infix_token;
		std::unique_ptr<Expression> left;
		std::unique_ptr<Expression> right;
		std::string infix_operator;
	};
}