#include "evaluator/evaluator.hpp"
#include "ast/integer_literal.hpp"
#include "ast/boolean_literal.hpp"
#include "ast/program.hpp"
#include "ast/expression_statement.hpp"
#include "ast/infix_expression.hpp"
#include "ast/prefix_expression.hpp"
#include "ast/if_expression.hpp"
#include "ast/block_statement.hpp"
#include "ast/identifier.hpp"
#include "object/integer.hpp"
#include "object/boolean.hpp"
#include "object/null.hpp"

#include <memory>

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

	// Helper function to evaluate prefix expressions
	static std::unique_ptr<Object> evalPrefixExpression(const std::string &operator_str, Object *right)
	{
		if (operator_str == "-")
		{
			auto *int_obj = dynamic_cast<Integer *>(right);
			if (int_obj)
			{
				return std::make_unique<Integer>(-int_obj->value);
			}
		}

		return getNull();
	}

	// Helper function to evaluate integer infix expressions
	static std::unique_ptr<Object> evalIntegerInfixExpression(const std::string &operator_str, Object *left, Object *right)
	{
		auto *left_int = dynamic_cast<Integer *>(left);
		auto *right_int = dynamic_cast<Integer *>(right);

		if (!left_int || !right_int)
		{
			return getNull();
		}

		int64_t left_val = left_int->value;
		int64_t right_val = right_int->value;

		if (operator_str == "+")
		{
			return std::make_unique<Integer>(left_val + right_val);
		}
		else if (operator_str == "-")
		{
			return std::make_unique<Integer>(left_val - right_val);
		}
		else if (operator_str == "*")
		{
			return std::make_unique<Integer>(left_val * right_val);
		}
		else if (operator_str == "/")
		{
			return std::make_unique<Integer>(left_val / right_val);
		}
		else if (operator_str == "<")
		{
			return nativeBoolToBooleanObject(left_val < right_val);
		}
		else if (operator_str == ">")
		{
			return nativeBoolToBooleanObject(left_val > right_val);
		}
		else if (operator_str == "==")
		{
			return nativeBoolToBooleanObject(left_val == right_val);
		}
		else if (operator_str == "!=")
		{
			return nativeBoolToBooleanObject(left_val != right_val);
		}

		return getNull();
	}

	// Helper function to evaluate infix expressions
	static std::unique_ptr<Object> evalInfixExpression(const std::string &operator_str, Object *left, Object *right)
	{
		if (left->get_type() == INTEGER_OBJ && right->get_type() == INTEGER_OBJ)
		{
			return evalIntegerInfixExpression(operator_str, left, right);
		}

		return getNull();
	}

	// Helper function to check if an object is truthy
	static bool isTruthy(Object *obj)
	{
		if (auto *null_obj = dynamic_cast<Null *>(obj))
		{
			return false;
		}
		if (auto *bool_obj = dynamic_cast<Boolean *>(obj))
		{
			return bool_obj->value;
		}
		return true; // integers and other objects are truthy
	}

	// Helper function to evaluate if expression
	static std::unique_ptr<Object> evalIfExpression(ast::IfExpression *ie)
	{
		auto condition = eval(ie->get_condition().get());

		if (isTruthy(condition.get()))
		{
			return eval(ie->get_consequence().get());
		}
		else if (ie->get_alternative())
		{
			return eval(ie->get_alternative().get());
		}
		else
		{
			return getNull();
		}
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

		if (auto *identifier = dynamic_cast<ast::Identifier *>(node))
		{
			if (identifier->identifier_name == "true")
			{
				return nativeBoolToBooleanObject(true);
			}
			else if (identifier->identifier_name == "false")
			{
				return nativeBoolToBooleanObject(false);
			}
			return getNull();
		}

		if (auto *boolean_literal = dynamic_cast<ast::BooleanLiteral *>(node))
		{
			return nativeBoolToBooleanObject(boolean_literal->get_value());
		}

		if (auto *prefix_expr = dynamic_cast<ast::PrefixExpression *>(node))
		{
			auto right = eval(prefix_expr->get_right_expression().get());
			return evalPrefixExpression(prefix_expr->get_prefix_operator(), right.get());
		}

		if (auto *infix_expr = dynamic_cast<ast::InfixExpression *>(node))
		{
			auto left = eval(infix_expr->get_left().get());
			auto right = eval(infix_expr->get_right().get());
			return evalInfixExpression(infix_expr->get_operator(), left.get(), right.get());
		}

		if (auto *block_stmt = dynamic_cast<ast::BlockStatement *>(node))
		{
			return evalStatements(block_stmt->get_statements());
		}

		if (auto *if_expr = dynamic_cast<ast::IfExpression *>(node))
		{
			return evalIfExpression(if_expr);
		}

		return nullptr;
	}
}
