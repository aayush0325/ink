#include "parser/parser.hpp"
#include <memory>

std::unique_ptr<ast::LetStatement> Parser::parse_let_statement()
{
	auto statement = std::make_unique<ast::LetStatement>(current_token);
	if (!expect_peek(TokenType::IDENT))
	{
		return nullptr;
	}

	// note that expect_peek() has advanced a token
	statement->ident = std::make_unique<ast::Identifier>(current_token, current_token.literal);

	if (!expect_peek(TokenType::ASSIGN))
	{
		return nullptr;
	}

	next_token(); // skip the '=' token
	statement->set_value(parse_expression(Precedence::LOWEST));

	if (peek_token.type == TokenType::SEMICOLON)
		next_token();

	return statement;
}
