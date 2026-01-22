#include "parser/parser.hpp"
#include <format>

bool Parser::expect_peek(const TokenType &t)
{
	if (peek_token.type == t)
	{
		next_token();
		return true;
	}
	peek_error(t);
	return false;
}

std::vector<std::string> Parser::get_errors()
{
	return errors;
}

void Parser::peek_error(const TokenType &t)
{
	std::string error = std::format(
		"expected token type: {}, got {}",
		static_cast<int>(t),
		static_cast<int>(peek_token.type));
	errors.push_back(error);
}

Precedence Parser::peek_precedence()
{
	auto it = precedences.find(peek_token.type);
	if (it != precedences.end())
	{
		return it->second;
	}
	return Precedence::LOWEST;
}

Precedence Parser::current_precedence()
{
	auto it = precedences.find(current_token.type);
	if (it != precedences.end())
	{
		return it->second;
	}
	return Precedence::LOWEST;
}
