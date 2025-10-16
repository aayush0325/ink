#include "ast/program.hpp"

std::string Program::token_literal()
{
	if (statements.empty())
		return "";
	else
		return statements.front()->token_literal();
}

std::string Program::get_string()
{
	std::string result = "";
	for (const auto &it : statements)
		result += it->get_string();
	return result;
}