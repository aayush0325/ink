#include "parser/parser.hpp"

std::unique_ptr<ast::ExpressionStatement> Parser::parse_expression_statement()
{
	std::unique_ptr<ast::ExpressionStatement> exp_stmt = std::make_unique<ast::ExpressionStatement>(current_token);
	exp_stmt->expression = parse_expression(Precedence::LOWEST);
	if (peek_token.type == TokenType::SEMICOLON)
		next_token();
	return exp_stmt;
}