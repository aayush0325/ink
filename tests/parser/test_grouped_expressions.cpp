#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <format>

void check_grouped_expressions()
{
	std::cout << "Test for grouped expressions parsing\n";
	std::cout << "Test starting\n";

	struct GroupedTest
	{
		std::string input;
		std::string expected;
	};

	std::vector<GroupedTest> tests = {
		{"1 + (2 + 3) + 4",
		 "((1 + (2 + 3)) + 4)"},
		{"(5 + 5) * 2",
		 "((5 + 5) * 2)"},
		{"2 / (5 + 5)",
		 "(2 / (5 + 5))"},
		{"-(5 + 5)",
		 "(-(5 + 5))"},
		{"!(true == true)",
		 "(!(true == true))"}};

	int error_count = 0;

	for (const auto &test : tests)
	{
		auto lexer = std::make_unique<Lexer>(test.input);
		auto parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		if (!program)
		{
			error_count++;
			std::cout << std::format("Failed - Program returned nullptr for input: {}",
									 test.input)
					  << std::endl;
			continue;
		}

		check_parser_errors(parser);

		std::string actual = program->get_string();
		if (actual != test.expected)
		{
			error_count++;
			std::cout << std::format("Failed - expected={}, got={}",
									 test.expected, actual)
					  << std::endl;
		}
	}

	if (error_count == 0)
		std::cout << "Test for grouped expressions parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for grouped expressions parsing ended ({} errors)\n\n", error_count);
}

