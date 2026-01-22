#include <gtest/gtest.h>
#include "evaluator/evaluator.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "object/integer.hpp"
#include "object/boolean.hpp"
#include "object/function.hpp"
#include "object/error.hpp"
#include <iostream>
#include <memory>

// Helper function to evaluate input string
static std::unique_ptr<Object> testEval(const std::string &input)
{
	auto lexer = std::make_unique<Lexer>(input);
	Parser parser(std::move(lexer));
	auto program = parser.parse_program();
	
	if (!parser.get_errors().empty()) {
		for (const auto& err : parser.get_errors()) {
			std::cout << "Parser error: " << err << std::endl;
		}
	}

	auto env = std::make_shared<Environment>();
	return evaluator::eval(program.get(), env);
}

// Helper function to test integer object
static void testIntegerObject(const std::unique_ptr<Object> &obj, int64_t expected)
{
	ASSERT_NE(obj, nullptr);
	auto *result = dynamic_cast<Integer *>(obj.get());
	ASSERT_NE(result, nullptr);
	EXPECT_EQ(result->value, expected);
}

TEST(EvaluatorTest, FunctionObject)
{
	std::string input = "fn(x) { x + 2; };";

	auto evaluated = testEval(input);
	auto *fn = dynamic_cast<Function *>(evaluated.get());
	ASSERT_NE(fn, nullptr);

	EXPECT_EQ(fn->parameters.size(), 1);
	EXPECT_EQ(fn->parameters[0]->get_string(), "x");

	std::string expectedBody = "(x + 2)";
	EXPECT_EQ(fn->body->get_string(), expectedBody);
}

TEST(EvaluatorTest, FunctionApplication)
{
	struct TestCase
	{
		std::string input;
		int64_t expected;
	};

	std::vector<TestCase> tests = {
		{"let identity = fn(x) { x; }; identity(5);", 5},
		{"let identity = fn(x) { return x; }; identity(5);", 5},
		{"let double = fn(x) { x * 2; }; double(5);", 10},
		{"let add = fn(x, y) { x + y; }; add(5, 5);", 10},
		{"let add = fn(x, y) { x + y; }; add(5 + 5, add(5, 5));", 20},
		{"fn(x) { x; }(5)", 5},
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		testIntegerObject(evaluated, tt.expected);
	}
}

TEST(EvaluatorTest, Closures)
{
	std::string input = R"(
		let newAdder = fn(x) {
			fn(y) { x + y };
		};
		let addTwo = newAdder(2);
		addTwo(2);
	)";

	testIntegerObject(testEval(input), 4);
}

TEST(EvaluatorTest, HigherOrderFunctions)
{
	std::string input = R"(
		let add = fn(x, y) { x + y };
		let applyFunc = fn(x, y, func) { func(x, y) };
		applyFunc(2, 2, add);
	)";

	testIntegerObject(testEval(input), 4);
}
