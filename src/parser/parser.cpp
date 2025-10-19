#include "parser/parser.hpp"

const std::map<TokenType, Precedence> Parser::precedences = {
	{TokenType::EQ, EQUALS},
	{TokenType::NEQ, EQUALS},
	{TokenType::LT, LESSGREATER},
	{TokenType::GT, LESSGREATER},
	{TokenType::PLUS, SUM},
	{TokenType::MINUS, SUM},
	{TokenType::SLASH, PRODUCT},
	{TokenType::ASTERISK, PRODUCT},
};

void Parser::next_token()
{
	current_token = peek_token;
	peek_token = lexer->next_token();
}

std::unique_ptr<ast::Program> Parser::parse_program()
{
	std::unique_ptr<ast::Program> program = std::make_unique<ast::Program>();
	while (current_token.type != TokenType::E_O_F)
	{
		std::unique_ptr<ast::Statement> statement = parse_statement();
		if (statement != nullptr)
		{
			program->statements.push_back(std::move(statement));
		}
		next_token();
	}
	return program;
}

std::unique_ptr<ast::Statement> Parser::parse_statement()
{
	switch (current_token.type)
	{
	case TokenType::LET:
		return parse_let_statement();

	case TokenType::RETURN:
		return parse_return_statement();
	default:
		return parse_expression_statement();
	}
}

std::unique_ptr<ast::Expression> Parser::parse_expression(Precedence precedence)
{
	auto it = prefix_lookup_table.find(current_token.type);
	if (it == prefix_lookup_table.end())
	{
		errors.push_back("no prefix function found in the lookup table");
		return nullptr;
	}
	auto prefix = it->second;
	auto left_exp = prefix();

	while (peek_token.type != TokenType::SEMICOLON && precedence < peek_precedence())
	{
		auto infix_it = infix_lookup_table.find(peek_token.type);
		if (infix_it == infix_lookup_table.end())
		{
			return left_exp;
		}
		auto infix = infix_it->second;
		next_token();
		left_exp = infix(std::move(left_exp));
	}
	return left_exp;
}
