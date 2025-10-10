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
		static_cast<int>(t),				 // or your own to_string(t)
		static_cast<int>(current_token.type) // assuming this is a std::string
	);
	errors.push_back(error);
}
