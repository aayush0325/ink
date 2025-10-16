#include "tests/lexer/test.hpp"
#include "tests/parser/test.hpp"
#include "tests/ast/test.hpp"

int main()
{
	test_basic_TokenType();
	test_full_code();
	test_code_complex();
	test_let_statement_noexpr();
	test_return_statement();
	run_all_ast_string_tests();
	check_identifier_expression_statements();
	check_integer_literal_statement();
}