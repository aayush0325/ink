#include "tests/lexer/test.hpp"
#include "tests/parser/test.hpp"
#include "tests/ast/test.hpp"
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
	test_let_statement_noexpr();
	test_return_statement();
	run_all_ast_string_tests();
	check_identifier_expression_statements();
	check_integer_literal_statement();
	check_prefix_expressions();
	check_operator_precedence_parsing();
	check_infix_expressions();
	check_grouped_expressions();
	check_if_expressions();
	check_function_literal();
	check_function_parameter_parsing();
	check_call_expressions();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
