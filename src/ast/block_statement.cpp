#include "ast/block_statement.hpp"

std::string ast::BlockStatement::get_string()
{
	std::string result = "";
	for (auto &it : statements)
		result += it->get_string();
	return result;
}

std::string ast::BlockStatement::token_literal()
{
	return token.literal;
}

void ast::BlockStatement::insert_statement(std::unique_ptr<Statement> stmt)
{
	statements.push_back(std::move(stmt));
}