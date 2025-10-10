#include "parser/parser.hpp"
#include <memory>

std::unique_ptr<ReturnStatement> Parser::parse_return_statement()
{
	std::unique_ptr<ReturnStatement> return_statement = std::make_unique<ReturnStatement>(current_token);
	next_token();
	while (current_token.type != TokenType::SEMICOLON)
		next_token();
	return return_statement;
}