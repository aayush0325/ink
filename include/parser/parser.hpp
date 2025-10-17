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
#include "ast/prefix_expression.hpp"
#include "ast/infix_expression.hpp"

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

	static const std::map<TokenType, Precedence> precedences;

	bool expect_peek(const TokenType &t);

	Precedence peek_precedence();

	Precedence current_precedence();

	std::unique_ptr<ast::Statement> parse_statement();

	std::unique_ptr<ast::LetStatement> parse_let_statement();

	std::unique_ptr<ast::ReturnStatement> parse_return_statement();

	std::unique_ptr<ast::ExpressionStatement> parse_expression_statement();

	std::unique_ptr<ast::Expression> parse_expression(Precedence x);

	void peek_error(const TokenType &t);

	std::unique_ptr<ast::Expression> prefix_parse_identifier();
	std::unique_ptr<ast::Expression> prefix_parse_integer_literal();
	std::unique_ptr<ast::Expression> prefix_parse_prefix_expression();
	std::unique_ptr<ast::Expression> infix_parse_infix_expression(std::unique_ptr<ast::Expression> left);

public:
	explicit Parser(std::unique_ptr<Lexer> l);

	void next_token();

	std::unique_ptr<ast::Program> parse_program();

	std::vector<std::string> get_errors();
};