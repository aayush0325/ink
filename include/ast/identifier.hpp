#pragma once

#include "token/token.hpp"
#include "ast/ast.hpp"

namespace ast
{
	// variables
	class Identifier : public Expression
	{
	public:
		virtual std::string token_literal();
		virtual std::string get_string();
		Identifier(Token token, std::string identifier_name) : token(token), identifier_name(identifier_name) {}
		Identifier() {}

		Token token; // the "IDENT" token
		std::string identifier_name;
	};
}