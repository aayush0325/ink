#include "parser/parser.hpp"
#include <memory>

std::unique_ptr<ast::ReturnStatement> Parser::parse_return_statement()
{
	auto return_statement = std::make_unique<ast::ReturnStatement>(current_token);
	next_token();
	// TODO: parse complete expression here
	while (current_token.type != TokenType::SEMICOLON)
		next_token();
	return return_statement;
}