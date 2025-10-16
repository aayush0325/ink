#include "parser/parser.hpp"

std::unique_ptr<Expression> Parser::prefix_parse_identifier()
{
	std::unique_ptr<Identifier> ident = std::make_unique<Identifier>(current_token, current_token.literal);
	return ident;
}