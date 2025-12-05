#include "parser/parser.hpp"
#include "tests/parser/test.hpp"
#include <gtest/gtest.h>
#include <format>
#include <iostream>

void check_parser_errors(Parser &parser)
{
	auto errors = parser.get_errors();
	if (errors.empty())
	{
		return;
	}

	std::string error_msg = std::format("Parser has {} errors:\n", errors.size());
	for (const auto &err : errors)
	{
		error_msg += std::format("  - {}\n", err);
	}
	
	FAIL() << error_msg;
}
