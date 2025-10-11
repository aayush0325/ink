#include "parser/parser.hpp"
#include <memory>

std::unique_ptr<LetStatement> Parser::parse_let_statement()
{
	std::unique_ptr<LetStatement> statement = std::make_unique<LetStatement>(current_token);
	if (!expect_peek(TokenType::IDENT))
	{
		return nullptr;
	}

	// note that expect_peek() has advanced a token
	statement->ident = std::make_unique<Identifier>(current_token, current_token.literal);

	if (!expect_peek(TokenType::ASSIGN))
	{
		return nullptr;
	}

	// note that expect_peek() has advanced a token again
	while (current_token.type != TokenType::SEMICOLON)
		next_token();

	return statement;
}
