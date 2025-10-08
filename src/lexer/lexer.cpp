#include "lexer/lexer.hpp"
#include "utils/utils.hpp"

Token Lexer::next_token()
{
	Token tok = Token();
	skip_whitespace();
	switch (ch)
	{
	case '=':
		if (peek_char() == '=')
		{
			read_char();
			tok = Token(TokenType::EQ, "==");
		}
		else
			tok = Token(TokenType::ASSIGN, "=");
		break;
	case ';':
		tok = Token(TokenType::SEMICOLON, ";");
		break;
	case '(':
		tok = Token(TokenType::LPAREN, "(");
		break;
	case ')':
		tok = Token(TokenType::RPAREN, ")");
		break;
	case ',':
		tok = Token(TokenType::COMMA, ",");
		break;
	case '+':
		tok = Token(TokenType::PLUS, "+");
		break;
	case '-':
		tok = Token(TokenType::MINUS, "-");
		break;
	case '*':
		tok = Token(TokenType::ASTERISK, "*");
		break;
	case '{':
		tok = Token(TokenType::LBRACE, "{");
		break;
	case '}':
		tok = Token(TokenType::RBRACE, "}");
		break;
	case '/':
		tok = Token(TokenType::SLASH, "/");
		break;
	case '>':
		if (peek_char() == '=')
		{
			read_char();
			tok = Token(TokenType::GTE, ">=");
		}
		else
			tok = Token(TokenType::GT, ">");
		break;
	case '<':
		if (peek_char() == '=')
		{
			read_char();
			tok = Token(TokenType::LTE, "<=");
		}
		else
			tok = Token(TokenType::LT, "<");
		break;
	case '!':
		if (peek_char() == '=')
		{
			read_char();
			tok = Token(TokenType::NEQ, "!=");
		}
		else
			tok = Token(TokenType::BANG, "!");
		break;
	case 0:
		tok = Token(TokenType::E_O_F, "");
		break;
	default:
		if (is_letter(ch))
		{
			std::string str = read_identifier();
			return Token(Token::lookupIdent(str), str); // early return to skip the read_char()
		}
		else if (is_number(ch))
		{
			std::string number = read_number();
			return Token(TokenType::INT, number); // early return to skip the read_char()
		}
		else
			tok = Token(TokenType::ILLEGAL, "");
		break;
	}

	read_char();
	return tok;
}

void Lexer::read_char()
{
	if (read_position >= input.size())
		ch = 0; // EOF
	else
		ch = input.at(read_position);

	position = read_position;
	read_position += 1;
}

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