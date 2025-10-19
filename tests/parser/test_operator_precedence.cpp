#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <format>

void check_operator_precedence_parsing()
{
	std::cout << "Test for operator precedence parsing\n";
	std::cout << "Test starting\n";

	struct PrecedenceTest
	{
		std::string input;
		std::string expected;
	};

	std::vector<PrecedenceTest> tests = {
		{"-a * b",
		 "((-a) * b)"},
		{"!-a",
		 "(!(-a))"},
		{"a + b + c",
		 "((a + b) + c)"},
		{"a + b - c",
		 "((a + b) - c)"},
		{"a * b * c",
		 "((a * b) * c)"},
		{"a * b / c",
		 "((a * b) / c)"},
		{"a + b / c",
		 "(a + (b / c))"},
		{"a + b * c + d / e - f",
		 "(((a + (b * c)) + (d / e)) - f)"},
		{"3 + 4; -5 * 5",
		 "(3 + 4)((-5) * 5)"},
		{"5 > 4 == 3 < 4",
		 "((5 > 4) == (3 < 4))"},
		{"5 < 4 != 3 > 4",
		 "((5 < 4) != (3 > 4))"},
		{"3 + 4 * 5 == 3 * 1 + 4 * 5",
		 "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"}};

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
		std::cout << "Test for operator precedence parsing ended (all passed)\n\n";
	else
		std::cout << std::format("Test for operator precedence parsing ended ({} errors)\n\n", error_count);
}
