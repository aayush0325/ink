#include "tests/ast/test.hpp"
#include <iostream>

void run_all_ast_string_tests()
{
	std::cout << "Test for all AST string representation tests\n";
	std::cout << "Test starting\n";

	test_identifier_string();
	test_let_statement_string();
	test_return_statement_string();
	test_program_string();
	test_program_multiple_statements();
	test_empty_program();

	std::cout << "Test for all AST string representation tests ended (all passed)\n\n";
}
