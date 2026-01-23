#include "parser/parser.hpp"
#include "ast/function_literal.hpp"
#include "token/token.hpp"

std::unique_ptr<ast::Expression> Parser::prefix_parse_function_literal()
{
	auto lit = std::make_unique<ast::FunctionLiteral>(current_token);

	if (!expect_peek(TokenType::LPAREN))
		return nullptr;

	auto params = parse_function_parameters();
	if (params.empty() && !errors.empty())
		return nullptr;

	lit->set_parameters(std::move(params));

	if (!expect_peek(TokenType::LBRACE))
		return nullptr;

	lit->set_body(std::move(parse_block_statement()));

	return lit;
}

std::vector<std::unique_ptr<ast::Identifier>> Parser::parse_function_parameters()
{
	std::vector<std::unique_ptr<ast::Identifier>> identifiers;

	if (peek_token.type == TokenType::RPAREN)
	{
		next_token();
		return identifiers;
	}

	next_token();

	auto ident = std::make_unique<ast::Identifier>(
		current_token, current_token.literal);

	identifiers.push_back(std::move(ident));

	while (peek_token.type == TokenType::COMMA)
	{
		next_token(); // consume comma
		next_token(); // consume identifier

		auto ident = std::make_unique<ast::Identifier>(
			current_token, current_token.literal);

		identifiers.push_back(std::move(ident));
	}

	if (!expect_peek(TokenType::RPAREN))
		return {};

	return identifiers;
}
