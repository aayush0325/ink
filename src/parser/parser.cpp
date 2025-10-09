#include "parser/parser.hpp"

void Parser::next_token()
{
	current_token = peek_token;
	peek_token = lexer->next_token();
}

std::unique_ptr<Program> Parser::parse_program()
{
	std::unique_ptr<Program> program = std::make_unique<Program>();
	while (current_token.type != TokenType::E_O_F)
	{
		std::unique_ptr<Statement> statement = parse_statement();
		if (statement != nullptr)
		{
			program->statements.push_back(std::move(statement));
		}
		next_token();
	}
	return program;
}

std::unique_ptr<Statement> Parser::parse_statement()
{
	switch (current_token.type)
	{
	case TokenType::LET:
		return parse_let_statement();

	default:
		return nullptr;
	}
}

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
	while (current_token.type != TokenType::SEMICOLON and current_token.type != TokenType::E_O_F)
		next_token();

	return statement;
}

bool Parser::expect_peek(const TokenType &t)
{
	if (peek_token.type == t)
	{
		next_token();
		return true;
	}
	return false;
}
