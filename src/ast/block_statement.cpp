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

std::unique_ptr<ast::Node> ast::BlockStatement::clone() const
{
	auto clone = std::make_unique<BlockStatement>(token);
	for (const auto &stmt : statements)
	{
		// Cast unique_ptr<Node> back to unique_ptr<Statement>
		auto stmt_clone = stmt->clone();
		clone->insert_statement(std::unique_ptr<Statement>(
			static_cast<Statement *>(stmt_clone.release())));
	}
	return clone;
}