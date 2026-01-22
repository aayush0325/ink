#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"
#include <memory>

namespace ast
{
	// Return statement, return 1;
	class ReturnStatement : public Statement
	{
	public:
		ReturnStatement(Token token) : token(token), return_value(nullptr) {}
		virtual std::string token_literal() override;
		virtual std::string get_string() override;
		virtual std::unique_ptr<Node> clone() const override;

		void set_return_value(std::unique_ptr<Expression> val);
		const std::unique_ptr<Expression> &get_return_value() const { return return_value; }

	private:
		Token token;							  // the return token
		std::unique_ptr<Expression> return_value; // the expression which has to be calculated and returned
	};
}