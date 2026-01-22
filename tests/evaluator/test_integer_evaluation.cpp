#include "evaluator/evaluator.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "object/integer.hpp"
#include "object/null.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <typeinfo>

// Helper function to evaluate input string
static std::unique_ptr<Object> testEval(const std::string &input)
{
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser(std::move(lexer));
	auto program = parser.parse_program();
	check_parser_errors(parser);
	auto env = std::make_shared<Environment>();
	return evaluator::eval(program.get(), env);
}

// Helper function to test integer object
static void testIntegerObject(Object *obj, int64_t expected)
{
	auto *integer_obj = dynamic_cast<Integer *>(obj);
	ASSERT_NE(integer_obj, nullptr) << "object is not Integer";

	EXPECT_EQ(integer_obj->value, expected);
}

TEST(EvaluatorTest, IntegerExpression)
{
	struct TestCase
	{
		std::string input;
		int64_t expected;
	};

	std::vector<TestCase> tests = {
		{"5", 5},
		{"10", 10},
		{"-5", -5},
		{"-10", -10},
		{"5 + 5 + 5 + 5 - 10", 10},
		{"2 * 2 * 2 * 2 * 2", 32},
		{"-50 + 100 + -50", 0},
		{"5 * 2 + 10", 20},
		{"5 + 2 * 10", 25},
		{"20 + 2 * -10", 0},
		{"50 / 2 * 2 + 10", 60},
		{"2 * (5 + 10)", 30},
		{"3 * 3 * 3 + 10", 37},
		{"3 * (3 * 3) + 10", 37},
		{"(5 + 10 * 2 + 15 / 3) * 2 + -10", 50},
		{"if (true) { 10 }", 10},
		{"if (1) { 10 }", 10},
		{"if (1 < 2) { 10 }", 10},
		{"if (1 < 2) { 10 } else { 20 }", 10},
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		ASSERT_NE(evaluated, nullptr) << "Evaluator returned nullptr";
		testIntegerObject(evaluated.get(), tt.expected);
	}
}
