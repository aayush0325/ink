#include "ast/identifier.hpp"

std::string Identifier::token_literal()
{
	return token.literal;
}

std::string Identifier::get_string()
{
	return identifier_name;
}