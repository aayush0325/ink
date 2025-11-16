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

/*
	Main pratt parsing algorithm.

	This is what the precedence table looks like:

	1. LOWEST -  placeholder for lowest, use for variables etc
	2. EQUALS -  =
	3. LESSGREATER - >, <, >=, <=
	4. SUM - +, -
	5. PRODUCT - *, /
	6. PREFIX - !
	7. CALL - somefunction()
*/
std::unique_ptr<ast::Expression> Parser::parse_expression(Precedence precedence)
{
	/*
		This part will check if our token is a prefix token. If it is not a
		prefix token then this should throw an error and return a null pointer.
		if it IS a prefix operator then we parse the expression on the left and
		start checking for infix operators.
	*/
	auto it = prefix_lookup_table.find(current_token.type);
	if (it == prefix_lookup_table.end())
	{
		errors.push_back("no prefix function found in the lookup table");
		return nullptr;
	}
	auto prefix = it->second;
	auto expr = prefix();

	/*
		While our current statement hasn't ended and the current precedence is
		lesser than the precedence of the next operator:

			1. check if there is an infix function for that token and return
			errors

			2. if infix function exists then the current expression will act as
			the LEFT side of the function and the right will be computed by
			calling this same function again with the current precedence of that
			token and not LOWEST: dry run 2 * 3 + 4 and 3 + 2 * 4 for better
			understanding, same logic runs for any expression

		It must be noted that this method is recursive for Infix expressions,
		the current token and peek token pointers are shared between two calls
		of this same function.

		The call stack looks something like this (if infix):

		parse_expression(p1) --> parse_expression(p2) --> ...
	*/
	while (peek_token.type != TokenType::SEMICOLON && precedence < peek_precedence())
	{
		auto infix_it = infix_lookup_table.find(peek_token.type);
		if (infix_it == infix_lookup_table.end())
		{
			return expr;
		}
		auto infix = infix_it->second;
		next_token();
		expr = infix(std::move(expr));
	}
	return expr;
}
