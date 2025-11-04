#include "parser/parser.hpp"

std::unique_ptr<ast::Expression> Parser::prefix_parse_identifier()
{
	auto ident = std::make_unique<ast::Identifier>(current_token, current_token.literal);
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

std::unique_ptr<ast::Expression> Parser::prefix_parse_boolean_literal()
{
	auto boolean_literal = std::make_unique<ast::BooleanLiteral>(current_token);
	return boolean_literal;
}

std::unique_ptr<ast::Expression> Parser::prefix_parse_prefix_expression()
{
	auto expr = std::make_unique<ast::PrefixExpression>(current_token, current_token.literal);
	next_token();
	expr->set_right_expression(parse_expression(Precedence::PREFIX));
	return expr;
}

std::unique_ptr<ast::Expression> Parser::prefix_parse_grouped_expression()
{
	next_token();
	auto expr = parse_expression(Precedence::LOWEST);
	if (!expect_peek(TokenType::RPAREN))
		return nullptr;
	return expr;
}