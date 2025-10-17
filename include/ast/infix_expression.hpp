#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	class InfixExpression : public Expression
	{
	public:
		std::string get_string();
		std::string token_literal();

		explicit InfixExpression(Token infix_token, std::unique_ptr<Expression> left, std::string infix_operator)
			: infix_token(infix_token), left(std::move(left)), right(nullptr), infix_operator(infix_operator) {}

		void set_right(std::unique_ptr<Expression> right);
		
		// Getter methods for testing
		const std::unique_ptr<Expression>& get_left() const { return left; }
		const std::unique_ptr<Expression>& get_right() const { return right; }
		const std::string& get_operator() const { return infix_operator; }

	private:
		Token infix_token;
		std::unique_ptr<Expression> left;
		std::unique_ptr<Expression> right;
		std::string infix_operator;
	};
}