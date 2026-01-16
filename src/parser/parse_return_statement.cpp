#include "parser/parser.hpp"
#include <memory>

std::unique_ptr<ast::ReturnStatement> Parser::parse_return_statement()
{
	auto return_statement = std::make_unique<ast::ReturnStatement>(current_token);
	next_token();
	return_statement->set_return_value(parse_expression(LOWEST));
	expect_peek(TokenType::SEMICOLON);
	return return_statement;
}
