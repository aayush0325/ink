#include "parser/parser.hpp"

Parser::Parser(std::unique_ptr<Lexer> l) : lexer(std::move(l))
{
	current_token = lexer->next_token();
	peek_token = lexer->next_token();
	errors.clear();

	prefix_lookup_table.insert({TokenType::IDENT, [this]()
								{
									return prefix_parse_identifier();
								}});

	prefix_lookup_table.insert({TokenType::INT, [this]()
								{
									return prefix_parse_integer_literal();
								}});

	prefix_lookup_table.insert({TokenType::BANG, [this]()
								{
									return prefix_parse_prefix_expression();
								}});

	prefix_lookup_table.insert({TokenType::MINUS, [this]()
								{
									return prefix_parse_prefix_expression();
								}});
}