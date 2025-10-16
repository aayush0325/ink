#include "ast/return_statement.hpp"

std::string ReturnStatement::token_literal()
{
	return token.literal; // the return token
}