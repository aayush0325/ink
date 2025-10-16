#include "parser/parser.hpp"

std::unique_ptr<ast::Expression> Parser::prefix_parse_identifier()
{
	std::unique_ptr<ast::Identifier> ident = std::make_unique<ast::Identifier>(current_token, current_token.literal);
	return ident;
}

std::unique_ptr<ast::Expression> Parser::prefix_parse_integer_literal()
{
	auto integer_literal = std::make_unique<ast::IntegerLiteral>(current_token);
	if (!integer_literal->set_integer_value_from_token())
	{
		errors.push_back("Cannot parse the token literal into an integer");
		return nullptr;
	}
	return integer_literal;
}