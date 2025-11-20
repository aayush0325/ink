#pragma once

#include "types/types.hpp"
#include <string>
#include <map>
#include <iostream>

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

	/*
		mark read only methods as const for const correctness and to tell the
		compiler that this method doesn't change anything.

		removing this causes a bug in the test suite with gtest

		/ink/tests/lexer/code_complex.cpp:113:3:   required from here
		gtest.h:1394:11: error: passing ‘const Token’ as ‘this’ argument discards qualifiers [-fpermissive]
		1394 |   if (lhs == rhs) {
			|       ~~~~^~~~~~
		In file included from /ink/include/lexer/lexer.hpp:4,
						from /ink/tests/lexer/code_complex.cpp:1:
		/ink/include/token/token.hpp:64:14: note:   in call to ‘bool Token::operator==(const Token&)’
		64 |         bool operator==(const Token &a)
			|              ^~~~~~~~
		gmake[2]: *** [CMakeFiles/tests.dir/build.make:160: CMakeFiles/tests.dir/tests/lexer/code_complex.cpp.o] Error 1
		gmake[1]: *** [CMakeFiles/Makefile2:139: CMakeFiles/tests.dir/all] Error 2
		gmake: *** [Makefile:91: all] Error 2
	*/
	bool operator==(const Token &a) const
	{
		return (type == a.type) and (literal == a.literal);
	}

	bool operator!=(const Token &a) const
	{
		return (type != a.type) or (literal != a.literal);
	}

	// enables std::cout << <SOMETOKEN>;
	friend std::ostream &operator<<(std::ostream &os, const Token &tok);

	static TokenType lookupIdent(const std::string &ident);
};