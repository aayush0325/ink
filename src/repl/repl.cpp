#include "repl/repl.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include <iostream>
#include <string>

void init_repl()
{
	std::string input;
	while (input != "quit")
	{
		std::cout << PROMPT;
		std::getline(std::cin, input); // read the whole line instead of the string till first whitespace
		Lexer lexer = Lexer(input);
		for (Token tok = lexer.next_token(); tok.type != TokenType::E_O_F; tok = lexer.next_token())
		{
			std::cout << tok << std::endl;
		}
	}
}