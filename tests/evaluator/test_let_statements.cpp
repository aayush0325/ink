#include "evaluator/evaluator.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "object/integer.hpp"
#include "object/environment.hpp"
#include <gtest/gtest.h>
#include <memory>

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

TEST(EvaluatorTest, LetStatements)
{
	struct TestCase
	{
		std::string input;
		int64_t expected;
	};

	std::vector<TestCase> tests = {
		{"let a = 5; a;", 5},
		{"let a = 5 * 5; a;", 25},
		{"let a = 5; let b = a; b;", 5},
		{"let a = 5; let b = a; let c = a + b + 5; c;", 15},
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		ASSERT_NE(evaluated, nullptr)
			<< "Evaluator returned nullptr for input: "
			<< tt.input;
		testIntegerObject(evaluated.get(), tt.expected);
	}
}
