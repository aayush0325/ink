#include "lexer/lexer.hpp"
#include "utils/utils.hpp"

void Lexer::skip_whitespace()
{
	while (ch == ' ' or ch == '\t' or ch == '\n' or ch == '\r')
		read_char();
}

std::string Lexer::read_identifier()
{
	u64 initial_position = position;
	while (is_letter(ch))
		read_char();
	u64 identifier_name_length = position - initial_position;
	std::string result(input, initial_position, identifier_name_length);
	return result;
}

std::string Lexer::read_number()
{
	u64 initial_position = position;
	while (is_number(ch))
		read_char();
	u64 number_length = position - initial_position;
	std::string result(input, initial_position, number_length);
	return result;
}

char Lexer::peek_char()
{
	if (read_position >= input.size())
		return 0;
	return input.at(read_position);
}