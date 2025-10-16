#pragma once

#include "types/types.hpp"
#include "token/token.hpp"

class IntegerLiteral : public Expression
{
	i64 integer_value;
	Token token;

public:
	std::string token_literal();
	std::string get_string();

	IntegerLiteral(Token token) : token(token) {}

	i64 get_value() { return integer_value; }

	bool set_integer_value_from_token();
};