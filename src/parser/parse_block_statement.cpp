#include "parser/parser.hpp"

std::unique_ptr<ast::BlockStatement> Parser::parse_block_statement()
{
	auto blockstmt = std::make_unique<ast::BlockStatement>(current_token);
	next_token(); // Skip past LBRACE

	while (current_token.type != TokenType::E_O_F and current_token.type != TokenType::RBRACE)
	{
		auto stmt = parse_statement();
		if (stmt != nullptr)
			blockstmt->insert_statement(std::move(stmt));
		next_token();
	}

	return blockstmt;
}
