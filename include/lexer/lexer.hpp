#pragma once

#include "types/types.hpp"
#include "token/token.hpp"

class Lexer
{
	// "explicit" stops unintended automatic conversions by requiring that constructor calls are made explicitly
	//  We can't define a lexer without an input
public:
	explicit Lexer(std::string input) : input(input), position(0), read_position(0), ch(0)
	{
		read_char(); // initialize the read_position and position pointers
		skip_whitespace();
	}

	Token next_token();

private:
	std::string input;
	u64 position;
	u64 read_position;
	char ch;

	void read_char();

	void skip_whitespace();

	std::string read_identifier();

	std::string read_number();

	std::string read_string();

	char peek_char();
};