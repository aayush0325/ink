#include "ast/program.hpp"

std::string ast::Program::token_literal()
{
	if (statements.empty())
		return "";
	else
		return statements.front()->token_literal();
}

std::string ast::Program::get_string()
{
	std::string result = "";
	for (const auto &it : statements)
		result += it->get_string();
	return result;
}

std::unique_ptr<ast::Node> ast::Program::clone() const
{
	auto clone = std::make_unique<Program>();
	for (const auto &stmt : statements)
	{
		auto stmt_clone = stmt->clone();
		clone->statements.push_back(std::unique_ptr<Statement>(
			static_cast<Statement *>(stmt_clone.release())));
	}
	return clone;
}