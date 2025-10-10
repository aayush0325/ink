#pragma once

#include <memory>
#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "ast/program/program.hpp"
#include "ast/let_statement/let_statement.hpp"
#include "ast/ast.hpp"

class Parser
{
private:
	std::unique_ptr<Lexer> lexer;
	Token current_token;
	Token peek_token;
	std::vector<std::string> errors;

	bool expect_peek(const TokenType &t);

	std::unique_ptr<Statement> parse_statement();

	std::unique_ptr<LetStatement> parse_let_statement();

	void peek_error(const TokenType &t);

public:
	explicit Parser(std::unique_ptr<Lexer> l) : lexer(std::move(l))
	{
		current_token = lexer->next_token();
		peek_token = lexer->next_token();
		errors.clear();
	}

	void next_token();

	std::unique_ptr<Program> parse_program();

	std::vector<std::string> get_errors();
};