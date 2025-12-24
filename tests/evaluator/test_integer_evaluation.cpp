#include "evaluator/evaluator.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "object/integer.hpp"
#include <gtest/gtest.h>
#include <format>
#include <memory>
#include <typeinfo>

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
	ASSERT_NE(integer_obj, nullptr) 
		<< std::format("object is not Integer. got={}", typeid(*obj).name());

	EXPECT_EQ(integer_obj->value, expected)
		<< std::format("object has wrong value. got={}, want={}",
					   integer_obj->value, expected);
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
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		ASSERT_NE(evaluated, nullptr) << "Evaluator returned nullptr";
		testIntegerObject(evaluated.get(), tt.expected);
	}
}
