#pragma once

#include <memory>
#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include "ast/program.hpp"
#include "ast/let_statement.hpp"
#include "ast/return_statement.hpp"
#include "ast/ast.hpp"
#include <map>
#include "types/types.hpp"
#include <functional>
#include <ast/expression_statement.hpp>
#include "ast/integer_literal.hpp"

enum Precedence
{
	LOWEST,
	EQUALS,
	LESSGREATER,
	SUM,
	PRODUCT,
	PREFIX,
	CALL
};

class Parser
{
private:
	std::unique_ptr<Lexer> lexer;
	Token current_token;
	Token peek_token;
	std::vector<std::string> errors;

	std::map<TokenType, infix_parse_function> infix_lookup_table;
	std::map<TokenType, prefix_parse_function> prefix_lookup_table;

	bool expect_peek(const TokenType &t);

	std::unique_ptr<Statement> parse_statement();

	std::unique_ptr<LetStatement> parse_let_statement();

	std::unique_ptr<ReturnStatement> parse_return_statement();

	std::unique_ptr<ExpressionStatement> parse_expression_statement();

	std::unique_ptr<Expression> parse_expression(Precedence x);

	void peek_error(const TokenType &t);

	std::unique_ptr<Expression> prefix_parse_identifier();
	std::unique_ptr<Expression> prefix_parse_integer_literal();

public:
	explicit Parser(std::unique_ptr<Lexer> l);

	void next_token();

	std::unique_ptr<Program> parse_program();

	std::vector<std::string> get_errors();
};