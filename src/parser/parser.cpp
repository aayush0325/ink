#include "parser/parser.hpp"

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

std::unique_ptr<ast::Expression> Parser::parse_expression(Precedence x)
{
	auto it = prefix_lookup_table.find(current_token.type);
	if (it == prefix_lookup_table.end())
	{
		errors.push_back("no prefix function found in the lookup table");
		return nullptr;
	}
	auto prefix = it->second;
	std::unique_ptr<ast::Expression> leftexpr = prefix();
	return leftexpr;
}