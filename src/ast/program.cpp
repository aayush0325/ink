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