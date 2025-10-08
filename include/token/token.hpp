#pragma once

#include "types/types.hpp"
#include <string>
#include <map>

enum TokenType
{
	ILLEGAL,
	E_O_F,

	IDENT,
	INT,

	ASSIGN,	   // =
	PLUS,	   // +
	MINUS,	   // -
	ASTERISK,  // *
	COMMA,	   // ,
	SEMICOLON, // ;
	BANG,	   // !
	SLASH,	   // /

	GT,	 // >
	LT,	 // <
	GTE, // >=
	LTE, // <=
	EQ,	 // ==
	NEQ, // !=

	LPAREN, // (
	RPAREN, // )
	LBRACE, // {
	RBRACE, // }

	FUNCTION, // fn
	LET,	  // let
	TRUE,	  // true
	FALSE,	  // false
	IF,		  // if
	ELSE,	  // else
	RETURN,	  // return
};

class Token
{
private:
	static const std::map<std::string, TokenType> keywords;

public:
	TokenType type;
	std::string literal;

	Token(TokenType type, std::string literal) : type(type), literal(literal) {}
	Token() : type(ILLEGAL), literal("") {}

	bool operator==(const Token &a)
	{
		return (type == a.type) and (literal == a.literal);
	}

	bool operator!=(const Token &a)
	{
		return (type != a.type) or (literal != a.literal);
	}

	static TokenType lookupIdent(const std::string &ident);
};