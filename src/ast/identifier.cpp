#include "ast/identifier.hpp"

std::string ast::Identifier::token_literal()
{
	return token.literal;
}

std::string ast::Identifier::get_string()
{
	return identifier_name;
}