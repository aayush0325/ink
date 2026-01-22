#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"
#include <vector>
#include <memory>

namespace ast
{
	class CallExpression : public Expression
	{
	public:
		virtual std::string get_string() override;
		virtual std::string token_literal() override;
		virtual std::unique_ptr<Node> clone() const override;

		// Getter methods for testing
		const std::unique_ptr<Expression> &get_function() const { return function; }
		const std::vector<std::unique_ptr<Expression>> &get_arguments() const { return arguments; }

		// Setter methods for parser
		void set_function(std::unique_ptr<Expression> func) { function = std::move(func); }
		void set_arguments(std::vector<std::unique_ptr<Expression>> &&args) { arguments = std::move(args); }

		CallExpression(Token token) : token(token), function(nullptr) {}

	private:
		Token token;						  // The '(' token
		std::unique_ptr<Expression> function; // Identifier or FunctionLiteral
		std::vector<std::unique_ptr<Expression>> arguments;
	};
}
