#pragma once

#include "types/types.hpp"
#include "token/token.hpp"

namespace ast
{
	// Just a number
	class IntegerLiteral : public Expression
	{
		i64 integer_value;
		Token token;

	public:
		virtual std::string token_literal() override;
		virtual std::string get_string() override;
		virtual std::unique_ptr<Node> clone() const override;

		IntegerLiteral(Token token) : token(token) {}

		i64 get_value() { return integer_value; }

		bool set_integer_value_from_token();
	};
}