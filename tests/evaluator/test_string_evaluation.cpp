#include <gtest/gtest.h>
#include "evaluator/evaluator.hpp"
#include "lexer/lexer.hpp"
#include "object/string.hpp"
#include "parser/parser.hpp"

TEST(EvaluatorTest, TestStringLiteral)
{
	std::string input = R"("Hello World!")";
	auto l = std::make_unique<Lexer>(input);
	Parser p(std::move(l));
	auto program = p.parse_program();
	auto env = std::make_shared<Environment>();
	auto evaluated = evaluator::eval(program.get(), env);

	ASSERT_NE(evaluated, nullptr);
	auto str = dynamic_cast<String *>(evaluated.get());
	ASSERT_NE(str, nullptr);
	EXPECT_EQ(str->get_value(), "Hello World!");
}
