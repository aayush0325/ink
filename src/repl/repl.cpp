#include "repl/repl.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "token/token.hpp"
#include <iostream>
#include <string>
#include <memory>

void print_parser_errors(const std::vector<std::string> &errors)
{
	for (const auto &msg : errors)
	{
		std::cout << "\t" << msg << "\n";
	}
}

void init_repl()
{
	std::string input;
	while (true)
	{
		std::cout << PROMPT;
		if (!std::getline(std::cin, input))
		{
			return;
		}
		if (input == "quit")
		{
			return;
		}
		if (input.empty())
		{
			continue;
		}

		auto lexer = std::make_unique<Lexer>(input);
		auto parser = std::make_unique<Parser>(std::move(lexer));
		auto program = parser->parse_program();

		auto errors = parser->get_errors();
		if (!errors.empty())
		{
			print_parser_errors(errors);
			continue;
		}

		std::cout << program->get_string() << "\n";
	}
}
