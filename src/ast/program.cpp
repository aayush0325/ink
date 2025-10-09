#include "ast/program/program.hpp"

std::string Program::token_literal()
{
	if (statements.empty())
		return "";
	else
		return statements.front().token_literal();
}