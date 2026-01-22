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

	prefix_lookup_table.insert({TokenType::TRUE, [this]()
								{
									return prefix_parse_boolean_literal();
								}});

	prefix_lookup_table.insert({TokenType::FALSE, [this]()
								{
									return prefix_parse_boolean_literal();
								}});

	prefix_lookup_table.insert({TokenType::LPAREN, [this]()
								{
									return prefix_parse_grouped_expression();
								}});

	prefix_lookup_table.insert({TokenType::IF, [this]()
								{
									return prefix_parse_if_expression();
								}});

	prefix_lookup_table.insert({TokenType::FUNCTION, [this]()
								{
									return prefix_parse_function_literal();
								}});

	infix_lookup_table.insert({TokenType::PLUS, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::MINUS, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::SLASH, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::ASTERISK, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::EQ, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::NEQ, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::LT, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::GT, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::LTE, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::GTE, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_infix_expression(std::move(left));
							   }});

	infix_lookup_table.insert({TokenType::LPAREN, [this](std::unique_ptr<ast::Expression> left)
							   {
								   return infix_parse_call_expression(std::move(left));
							   }});
}
