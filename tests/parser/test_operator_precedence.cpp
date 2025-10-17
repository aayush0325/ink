#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "ast/expression_statement.hpp"
#include <format>

void check_operator_precedence_parsing()
{
	std::cout << "starting test for operator precedence parsing" << std::endl;

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

	for (const auto &test : tests)
	{
		auto lexer = std::make_unique<Lexer>(test.input);
		auto parser = Parser(std::move(lexer));
		auto program = parser.parse_program();

		if (!program)
		{
			std::cout << std::format("Program returned nullptr for input: {}",
									 test.input)
					  << std::endl;
			return;
		}

		check_parser_errors(parser);

		std::string actual = program->get_string();
		if (actual != test.expected)
		{
			std::cout << std::format("expected={}, got={}",
									 test.expected, actual)
					  << std::endl;
			return;
		}
	}

	std::cout << "test for operator precedence parsing has passed!" << std::endl;
}
