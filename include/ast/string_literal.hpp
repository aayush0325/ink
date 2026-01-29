#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast
{
	class StringLiteral : public Expression
	{
		std::string value;
		Token token;

	public:
		StringLiteral(Token token) : token(token), value(token.literal) {}

		virtual std::string token_literal() override;
		virtual std::string get_string() override;
		virtual std::unique_ptr<Node> clone() const override;

		std::string get_value() { return value; }
	};
}
