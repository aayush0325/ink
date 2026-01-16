#include "evaluator/evaluator.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "object/integer.hpp"
#include "object/boolean.hpp"
#include "object/null.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <iostream>
#include <sstream>

// Helper function to evaluate input string
static std::unique_ptr<Object> testEval(const std::string &input)
{
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser(std::move(lexer));
	auto program = parser.parse_program();
	check_parser_errors(parser);
	return evaluator::eval(program.get());
}

// Helper function to test integer object
static void testIntegerObject(Object *obj, int64_t expected)
{
	auto *integer_obj = dynamic_cast<Integer *>(obj);
	ASSERT_NE(integer_obj, nullptr) << "object is not Integer";

	EXPECT_EQ(integer_obj->value, expected);
}

// Helper function to test null object
static void testNullObject(Object *obj)
{
	auto *null_obj = dynamic_cast<Null *>(obj);
	ASSERT_NE(null_obj, nullptr) << "object is not NULL";
}

TEST(EvaluatorTest, IfElseExpressionsInteger)
{
	struct TestCase
	{
		std::string input;
		int64_t expected_int;
		bool is_null;
	};

	std::vector<TestCase> tests = {
		{"if (true) { 10 }", 10, false},
		{"if (false) { 10 }", 0, true},
		{"if (1) { 10 }", 10, false},
		{"if (1 < 2) { 10 }", 10, false},
		{"if (1 > 2) { 10 }", 0, true},
		{"if (1 > 2) { 10 } else { 20 }", 20, false},
		{"if (1 < 2) { 10 } else { 20 }", 10, false},
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		ASSERT_NE(evaluated, nullptr) << "Evaluator returned nullptr";

		if (!tt.is_null)
		{
			testIntegerObject(evaluated.get(), tt.expected_int);
		}
		else
		{
			testNullObject(evaluated.get());
		}
	}
}
