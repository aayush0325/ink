#include "ast/boolean_literal.hpp"

std::string ast::BooleanLiteral::get_string()
{
	return token.literal;
}

std::string ast::BooleanLiteral::token_literal()
{
	return token.literal;
}

std::unique_ptr<ast::Node> ast::BooleanLiteral::clone() const
{
	return std::make_unique<BooleanLiteral>(token);
}

bool ast::BooleanLiteral::operator==(const BooleanLiteral &l) const
{
	return (l.token == token) and (value == l.value);
}
