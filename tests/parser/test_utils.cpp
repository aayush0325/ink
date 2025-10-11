#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <format>
#include <iostream>

void check_parser_errors(Parser &parser)
{
	if (parser.get_errors().size() == 0)
		return;
	std::cout << std::format("error: parser has {} errors\n",
							 parser.get_errors().size());
	for (auto &it : parser.get_errors())
		std::cout << std::format("  - {}\n", it);
}
