#include "evaluator/evaluator.hpp"
#include "ast/integer_literal.hpp"
#include "ast/boolean_literal.hpp"
#include "ast/program.hpp"
#include "ast/expression_statement.hpp"
#include "object/integer.hpp"
#include "object/boolean.hpp"
#include "object/null.hpp"

namespace evaluator
{
	// Helper function to get NULL object
	static std::unique_ptr<Object> getNull()
	{
		return std::make_unique<Null>();
	}

	// Helper function to convert native bool to Boolean object
	static std::unique_ptr<Object> nativeBoolToBooleanObject(bool input)
	{
		return std::make_unique<Boolean>(input);
	}

	// Helper function to evaluate a list of statements
	static std::unique_ptr<Object> evalStatements(const std::vector<std::unique_ptr<ast::Statement>> &statements)
	{
		std::unique_ptr<Object> result = nullptr;

		for (const auto &statement : statements)
		{
			result = eval(statement.get());
		}

		return result;
	}

	std::unique_ptr<Object> eval(ast::Node *node)
	{
		// Statements
		if (auto *program = dynamic_cast<ast::Program *>(node))
		{
			return evalStatements(program->statements);
		}

		if (auto *expr_stmt = dynamic_cast<ast::ExpressionStatement *>(node))
		{
			return eval(expr_stmt->expression.get());
		}

		// Expressions
		if (auto *integer_literal = dynamic_cast<ast::IntegerLiteral *>(node))
		{
			return std::make_unique<Integer>(integer_literal->get_value());
		}

		if (auto *boolean_literal = dynamic_cast<ast::BooleanLiteral *>(node))
		{
			return nativeBoolToBooleanObject(boolean_literal->get_value());
		}

		return nullptr;
	}
}
