#include "ast/identifier.hpp"

std::string ast::Identifier::token_literal()
{
	return token.literal;
}

std::string ast::Identifier::get_string()
{
	return identifier_name;
}

std::unique_ptr<ast::Node> ast::Identifier::clone() const
{
	return std::make_unique<Identifier>(token, identifier_name);
}
