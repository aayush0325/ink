#include "evaluator/evaluator.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "object/boolean.hpp"
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
	auto env = std::make_shared<Environment>();
	return evaluator::eval(program.get(), env);
}

// Helper function to test boolean object
static void testBooleanObject(Object *obj, bool expected)
{
	auto *boolean_obj = dynamic_cast<Boolean *>(obj);
	ASSERT_NE(boolean_obj, nullptr) 
		<< std::format("object is not Boolean. got={}", typeid(*obj).name());

	EXPECT_EQ(boolean_obj->value, expected)
		<< std::format("object has wrong value. got={}, want={}",
					   boolean_obj->value, expected);
}

TEST(EvaluatorTest, BooleanExpression)
{
	struct TestCase
	{
		std::string input;
		bool expected;
	};

	std::vector<TestCase> tests = {
		{"true", true},
		{"false", false},
		{"1 < 2", true},
		{"1 > 2", false},
		{"1 < 1", false},
		{"1 > 1", false},
		{"1 == 1", true},
		{"1 != 1", false},
		{"1 == 2", false},
		{"1 != 2", true},
		{"!true", false},
		{"!false", true},
		{"!5", false},
		{"!!true", true},
		{"!!false", false},
		{"!!5", true},
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		ASSERT_NE(evaluated, nullptr) << "Evaluator returned nullptr";
		testBooleanObject(evaluated.get(), tt.expected);
	}
}
