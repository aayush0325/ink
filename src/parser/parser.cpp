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

	case TokenType::RETURN:
		return parse_return_statement();
	default:
		return nullptr;
	}
}
