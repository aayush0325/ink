#include "tests/ast/test.hpp"
#include <iostream>

void run_all_ast_string_tests()
{
	std::cout << "Running AST string representation tests...\n\n";

	test_identifier_string();
	test_let_statement_string();
	test_return_statement_string();
	test_program_string();
	test_program_multiple_statements();
	test_empty_program();

	std::cout << "\nAll AST string representation tests completed.\n";
}
