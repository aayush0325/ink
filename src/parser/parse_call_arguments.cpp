#include "parser/parser.hpp"

std::vector<std::unique_ptr<ast::Expression>> Parser::parse_call_arguments()
{
	std::vector<std::unique_ptr<ast::Expression>> args;

	if (peek_token.type == TokenType::RPAREN)
	{
		next_token();
		return args;
	}

	next_token();
	args.push_back(parse_expression(Precedence::LOWEST));

	while (peek_token.type == TokenType::COMMA)
	{
		next_token(); // consume comma
		next_token(); // consume next token
		args.push_back(parse_expression(Precedence::LOWEST));
	}

	if (!expect_peek(TokenType::RPAREN))
		return {};

	return args;
}
