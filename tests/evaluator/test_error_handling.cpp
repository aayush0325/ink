#include "evaluator/evaluator.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "tests/parser/test.hpp"
#include "object/error.hpp"
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

TEST(EvaluatorTest, ErrorHandling)
{
	struct TestCase
	{
		std::string input;
		std::string expectedMessage;
	};

	std::vector<TestCase> tests = {
		{
			"5 + true;",
			"type mismatch: INTEGER + BOOLEAN",
		},
		{
			"5 + true; 5;",
			"type mismatch: INTEGER + BOOLEAN",
		},
		{
			"-true",
			"unknown operator: -BOOLEAN",
		},
		{
			"true + false;",
			"unknown operator: BOOLEAN + BOOLEAN",
		},
		{
			"5; true + false; 5",
			"unknown operator: BOOLEAN + BOOLEAN",
		},
		{
			"if (10 > 1) { true + false; }",
			"unknown operator: BOOLEAN + BOOLEAN",
		},
		{
			"if (10 > 1) {\n"
			"  if (10 > 1) {\n"
			"    return true + false;\n"
			"  }\n"
			"  return 1;\n"
			"}",
			"unknown operator: BOOLEAN + BOOLEAN",
		},
		{
			"foobar",
			"identifier not found: foobar",
		},
	};

	for (const auto &tt : tests)
	{
		auto evaluated = testEval(tt.input);
		ASSERT_NE(evaluated, nullptr) << "Evaluator returned nullptr for input: " << tt.input;
		
		auto *errObj = dynamic_cast<Error *>(evaluated.get());
		ASSERT_NE(errObj, nullptr) << "no error object returned. got=" << evaluated->get_type() << " for input: " << tt.input;
		
		EXPECT_EQ(errObj->message, tt.expectedMessage) << "wrong error message for input: " << tt.input;
	}
}
