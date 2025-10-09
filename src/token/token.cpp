#include "token/token.hpp"

const std::map<std::string, TokenType> Token::keywords = {
	{"fn", FUNCTION},
	{"let", LET},
	{"if", IF},
	{"else", ELSE},
	{"return", RETURN},
	{"true", TRUE},
	{"false", FALSE},
};

TokenType Token::lookupIdent(const std::string &ident)
{
	auto it = keywords.find(ident);
	if (it != keywords.end())
		return it->second;
	return IDENT;
}

std::ostream &operator<<(std::ostream &os, const Token &tok)
{
	os << "{ " << tok.type << ", " << tok.literal << " }";
	return os;
}