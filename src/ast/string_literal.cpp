#include "ast/string_literal.hpp"

std::string ast::StringLiteral::token_literal()
{
	return token.literal;
}

std::string ast::StringLiteral::get_string()
{
	return token.literal;
}

std::unique_ptr<ast::Node> ast::StringLiteral::clone() const
{
	return std::make_unique<StringLiteral>(token);
}
