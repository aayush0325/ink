#include "repl/repl.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "evaluator/evaluator.hpp"
#include "token/token.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <readline/readline.h>
#include <readline/history.h>

void print_parser_errors(const std::vector<std::string> &errors)
{
	for (const auto &msg : errors)
	{
		std::cout << "\t" << msg << "\n";
	}
}

static int count_braces(const std::string &input)
{
	int depth = 0;
	for (char ch : input)
	{
		if (ch == '{')
			depth++;
		else if (ch == '}')
			depth--;
	}
	return depth;
}

static bool is_input_complete(const std::string &input)
{
	if (input == "quit\n" || input == "exit\n" || input == "clear()\n")
	{
		return true;
	}

	if (count_braces(input) > 0)
	{
		return false;
	}

	size_t last_pos = input.find_last_not_of(" \t\n\r");
	if (last_pos != std::string::npos && input[last_pos] == ';')
	{
		return true;
	}

	return false;
}

static int handle_enter(int count, int key)
{
	std::string input = rl_line_buffer;
	input += "\n";

	if (is_input_complete(input))
	{
		return rl_newline(count, key);
	}

	// Not complete, insert newline and indentation
	rl_insert_text("\n");
	int depth = count_braces(input);
	if (depth > 0)
	{
		std::string tabs(depth, '\t');
		rl_insert_text(tabs.c_str());
	}
	return 0;
}

static int handle_up(int count, int key)
{
	int cursor = rl_point;
	char *buffer = rl_line_buffer;

	// Find the start of the current line
	int line_start = cursor;
	while (line_start > 0 && buffer[line_start - 1] != '\n')
	{
		line_start--;
	}

	if (line_start == 0)
	{
		// At the first line, fall back to history
		return rl_get_previous_history(count, key);
	}

	// Move to the previous line
	int prev_line_start = line_start - 1;
	while (prev_line_start > 0 && buffer[prev_line_start - 1] != '\n')
	{
		prev_line_start--;
	}

	int column = cursor - line_start;
	int prev_line_end = line_start - 1;
	int prev_line_len = prev_line_end - prev_line_start;

	rl_point = prev_line_start + std::min(column, prev_line_len);
	return 0;
}

static int handle_down(int count, int key)
{
	int cursor = rl_point;
	char *buffer = rl_line_buffer;
	int len = rl_end;

	// Find the end of the current line
	int line_end = cursor;
	while (line_end < len && buffer[line_end] != '\n')
	{
		line_end++;
	}

	if (line_end == len)
	{
		// At the last line, fall back to history
		return rl_get_next_history(count, key);
	}

	// Move to the next line
	int next_line_start = line_end + 1;
	int next_line_end = next_line_start;
	while (next_line_end < len && buffer[next_line_end] != '\n')
	{
		next_line_end++;
	}

	// Find start of current line to calculate column
	int line_start = cursor;
	while (line_start > 0 && buffer[line_start - 1] != '\n')
	{
		line_start--;
	}

	int column = cursor - line_start;
	int next_line_len = next_line_end - next_line_start;

	rl_point = next_line_start + std::min(column, next_line_len);
	return 0;
}

void init_repl()
{
	auto env = std::make_shared<Environment>();

	// Configure readline
	rl_bind_key('\t', rl_insert);
	rl_bind_key('\n', handle_enter);
	rl_bind_key('\r', handle_enter);

	// Bind arrow keys for intra-buffer navigation
	// Note: These escape sequences might vary, but these are standard for many terminals
	rl_bind_keyseq("\033[A", handle_up);
	rl_bind_keyseq("\033[B", handle_down);

	// Ensure multi-line buffers wrap correctly
	rl_variable_bind("horizontal-scroll-mode", "off");

	while (true)
	{
		char *input_ptr = readline(PROMPT.c_str());
		if (!input_ptr)
		{
			break;
		}

		std::string input(input_ptr);
		free(input_ptr);

		if (input == "quit" || input == "exit")
		{
			break;
		}

		if (input == "clear()")
		{
			std::cout << "\033[2J\033[H" << std::flush;
			continue;
		}

		if (input.empty())
		{
			continue;
		}

		add_history(input.c_str());

		auto lexer = std::make_unique<Lexer>(input);
		auto parser = std::make_unique<Parser>(std::move(lexer));
		auto program = parser->parse_program();

		auto errors = parser->get_errors();
		if (!errors.empty())
		{
			print_parser_errors(errors);
		}
		else
		{
			auto evaluated = evaluator::eval(program.get(), env);
			if (evaluated != nullptr)
			{
				std::cout << evaluated->inspect() << "\n";
			}
		}
	}
}
