#include "parser/parser.hpp"
#include "ast/if_expression.hpp"
#include "token/token.hpp"

std::unique_ptr<ast::Expression> Parser::prefix_parse_if_expression()
{
	auto ifexpr = std::make_unique<ast::IfExpression>(current_token);
	if (!expect_peek(TokenType::LPAREN))
		return nullptr;
	next_token();
	ifexpr->set_condition(std::move(parse_expression(Precedence::LOWEST)));
	if (!expect_peek(TokenType::RPAREN))
		return nullptr;

	if (!expect_peek(TokenType::LBRACE))
		return nullptr;

	ifexpr->set_consequence(std::move(parse_block_statement()));

	if (peek_token.type == TokenType::ELSE)
	{
		next_token();

		if (!expect_peek(TokenType::LBRACE))
			return nullptr;

		ifexpr->set_alternative(std::move(parse_block_statement()));
	}

	return ifexpr;
}