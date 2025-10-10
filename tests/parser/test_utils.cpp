#include <iostream>
#include "tests/parser/test.hpp"
#include "parser/parser.hpp"

void check_parser_errors(Parser &parser)
{
	if (parser.get_errors().size() == 0)
		return;
	std::cout << "the parser has: " << parser.get_errors().size() << " errors" << std::endl;
	for (auto &it : parser.get_errors())
		std::cout << it << std::endl;
}
