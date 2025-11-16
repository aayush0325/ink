#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"
#include "block_statement.hpp"

namespace ast
{
	class IfExpression : public Expression
	{
	public:
		std::string token_literal();
		std::string get_string();
		void set_condition(std::unique_ptr<Expression> condition);
		void set_consequence(std::unique_ptr<BlockStatement> consequence);
		void set_alternative(std::unique_ptr<BlockStatement> alternative);

		// Getter methods for testing
		const std::unique_ptr<Expression> &get_condition() const { return condition; }
		const std::unique_ptr<BlockStatement> &get_consequence() const { return consequence; }
		const std::unique_ptr<BlockStatement> &get_alternative() const { return alternative; }

		IfExpression(Token token)
			: token(token), condition(nullptr), consequence(nullptr), alternative(nullptr) {}

	private:
		Token token; // if token
		std::unique_ptr<Expression> condition;
		std::unique_ptr<BlockStatement> consequence;
		std::unique_ptr<BlockStatement> alternative;
	};
}
