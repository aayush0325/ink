#pragma once

#include <memory>
#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "ast/program/program.hpp"
#include "ast/let_statement/let_statement.hpp"
#include "ast/ast.hpp"

class Parser
{
	std::unique_ptr<Lexer> lexer;
	Token current_token;
	Token peek_token;

	bool expect_peek(const TokenType &t);

	std::unique_ptr<Statement> parse_statement();

	std::unique_ptr<LetStatement> parse_let_statement();

public:
	explicit Parser(std::unique_ptr<Lexer> l) : lexer(std::move(l))
	{
		lexer->next_token();
		lexer->next_token();
	}

	void next_token();

	std::unique_ptr<Program> parse_program();
};