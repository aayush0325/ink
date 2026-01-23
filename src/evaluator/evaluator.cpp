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
#include "ast/return_statement.hpp"
#include "ast/let_statement.hpp"
#include "ast/function_literal.hpp"
#include "ast/call_expression.hpp"
#include "object/integer.hpp"
#include "object/boolean.hpp"
#include "object/null.hpp"
#include "object/error.hpp"
#include "object/return_value.hpp"
#include "object/environment.hpp"
#include "object/function.hpp"

#include <memory>
#include <format>
#include <vector>

namespace evaluator
{
	// Forward declarations
	static std::unique_ptr<Object> eval_identifier(
		ast::Identifier *node,
		std::shared_ptr<Environment> env);

	static std::unique_ptr<Object> apply_function(
		Object *fn,
		const std::vector<std::unique_ptr<Object>> &args);

	static std::shared_ptr<Environment> extend_function_env(
		Function *fn,
		const std::vector<std::unique_ptr<Object>> &args);

	static std::unique_ptr<Object> unwrap_return_value(
		std::unique_ptr<Object> obj);

	// Helper function to get NULL object
	static std::unique_ptr<Object> getNull()
	{
		return std::make_unique<Null>();
	}

	// Helper function to convert native bool to Boolean object
	static std::unique_ptr<Object> native_bool_to_bool_object(bool input)
	{
		return std::make_unique<Boolean>(input);
	}

	// Helper function to create a new Error object
	template <typename... Args>
	static std::unique_ptr<Object> new_error(std::string_view format_str,
											 Args &&...args)
	{
		return std::make_unique<Error>(
			std::vformat(format_str, std::make_format_args(args...)));
	}

	// Helper function to check if an object is an error
	static bool is_error(Object *obj)
	{
		if (obj != nullptr)
		{
			return obj->get_type() == ERROR_OBJ;
		}
		return false;
	}

	// Helper function to evaluate a list of statements (for BlockStatement)
	static std::unique_ptr<Object> eval_block_stmt(
		const std::vector<std::unique_ptr<ast::Statement>> &statements,
		std::shared_ptr<Environment> env)
	{
		std::unique_ptr<Object> result = nullptr;

		for (const auto &statement : statements)
		{
			result = eval(statement.get(), env);
			if (result != nullptr)
			{
				if (result->get_type() == RETURN_VALUE_OBJ ||
					result->get_type() == ERROR_OBJ)
				{
					return result;
				}
			}
		}

		return result;
	}

	// Helper function to evaluate a program
	static std::unique_ptr<Object> eval_program(
		const std::vector<std::unique_ptr<ast::Statement>> &statements,
		std::shared_ptr<Environment> env)
	{
		std::unique_ptr<Object> result = nullptr;

		for (const auto &statement : statements)
		{
			result = eval(statement.get(), env);
			if (result != nullptr)
			{
				if (result->get_type() == RETURN_VALUE_OBJ)
				{
					auto *return_val = dynamic_cast<ReturnValue *>(result.get());
					return std::move(return_val->value);
				}
				if (result->get_type() == ERROR_OBJ)
				{
					return result;
				}
			}
		}

		return result;
	}

	// Helper function to evaluate bang operator expressions
	static std::unique_ptr<Object> eval_bang_op_expr(Object *right)
	{
		if (auto *bool_obj = dynamic_cast<Boolean *>(right))
		{
			return native_bool_to_bool_object(!bool_obj->value);
		}
		if (dynamic_cast<Null *>(right))
		{
			return native_bool_to_bool_object(true);
		}
		// Any other object is truthy, so its negation is false
		return native_bool_to_bool_object(false);
	}

	// Helper function to evaluate prefix expressions
	static std::unique_ptr<Object> eval_prefix_expression(
		const std::string &operator_str,
		Object *right)
	{
		if (operator_str == "!")
		{
			return eval_bang_op_expr(right);
		}
		if (operator_str == "-")
		{
			auto *int_obj = dynamic_cast<Integer *>(right);
			if (int_obj)
			{
				return std::make_unique<Integer>(-int_obj->value);
			}
			return new_error("unknown operator: -{}", right->get_type());
		}

		return new_error("unknown operator: {}{}",
						 operator_str, right->get_type());
	}

	// Helper function to evaluate integer infix expressions
	static std::unique_ptr<Object> eval_int_infix_expr(
		const std::string &operator_str,
		Object *left, Object *right)
	{
		auto *left_int = dynamic_cast<Integer *>(left);
		auto *right_int = dynamic_cast<Integer *>(right);

		if (!left_int || !right_int)
		{
			return new_error("type mismatch: {} {} {}", left->get_type(),
							 operator_str, right->get_type());
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
			return native_bool_to_bool_object(left_val < right_val);
		}
		else if (operator_str == ">")
		{
			return native_bool_to_bool_object(left_val > right_val);
		}
		else if (operator_str == ">=")
		{
			return native_bool_to_bool_object(left_val >= right_val);
		}
		else if (operator_str == "<=")
		{
			return native_bool_to_bool_object(left_val <= right_val);
		}
		else if (operator_str == "==")
		{
			return native_bool_to_bool_object(left_val == right_val);
		}
		else if (operator_str == "!=")
		{
			return native_bool_to_bool_object(left_val != right_val);
		}

		return new_error("unknown operator: {} {} {}", left->get_type(),
						 operator_str, right->get_type());
	}

	// Helper function to evaluate infix expressions
	static std::unique_ptr<Object> eval_infix_expr(
		const std::string &operator_str,
		Object *left, Object *right)
	{
		if (left->get_type() == INTEGER_OBJ && right->get_type() == INTEGER_OBJ)
		{
			return eval_int_infix_expr(operator_str, left, right);
		}

		if (left->get_type() != right->get_type())
		{
			return new_error("type mismatch: {} {} {}", left->get_type(),
							 operator_str, right->get_type());
		}

		return new_error("unknown operator: {} {} {}", left->get_type(),
						 operator_str, right->get_type());
	}

	// Helper function to check if an object is truthy
	static bool is_truthy(Object *obj)
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

	// Helper function to evaluate identifiers
	static std::unique_ptr<Object> eval_identifier(
		ast::Identifier *node,
		std::shared_ptr<Environment> env)
	{
		auto val = env->get(node->identifier_name);
		if (val)
		{
			return val;
		}

		// Check for built-in booleans
		if (node->identifier_name == "true")
		{
			return native_bool_to_bool_object(true);
		}
		else if (node->identifier_name == "false")
		{
			return native_bool_to_bool_object(false);
		}

		return new_error("identifier not found: {}", node->identifier_name);
	}

	// Helper function to evaluate if expression
	static std::unique_ptr<Object> eval_if_expr(
		ast::IfExpression *ie,
		std::shared_ptr<Environment> env)
	{
		auto condition = eval(ie->get_condition().get(), env);
		if (is_error(condition.get()))
		{
			return condition;
		}

		if (is_truthy(condition.get()))
		{
			return eval(ie->get_consequence().get(), env);
		}
		else if (ie->get_alternative())
		{
			return eval(ie->get_alternative().get(), env);
		}
		else
		{
			return getNull();
		}
	}

	// Helper function to evaluate expressions
	static std::vector<std::unique_ptr<Object>> eval_expressions(
		const std::vector<std::unique_ptr<ast::Expression>> &exps,
		std::shared_ptr<Environment> env)
	{
		std::vector<std::unique_ptr<Object>> result;

		for (const auto &e : exps)
		{
			auto evaluated = eval(e.get(), env);
			if (is_error(evaluated.get()))
			{
				result.clear();
				result.push_back(std::move(evaluated));
				return result;
			}
			result.push_back(std::move(evaluated));
		}

		return result;
	}

	static std::unique_ptr<Object> apply_function(
		Object *fn,
		const std::vector<std::unique_ptr<Object>> &args)
	{
		auto *function = dynamic_cast<Function *>(fn);
		if (!function)
		{
			return new_error("not a function: {}", fn->get_type());
		}

		auto extendedEnv = extend_function_env(function, args);
		auto evaluated = eval(function->body.get(), extendedEnv);
		return unwrap_return_value(std::move(evaluated));
	}

	static std::shared_ptr<Environment> extend_function_env(
		Function *fn,
		const std::vector<std::unique_ptr<Object>> &args)
	{
		auto env = Environment::NewEnclosedEnvironment(fn->env);

		for (size_t i = 0; i < fn->parameters.size(); ++i)
		{
			env->set(fn->parameters[i]->identifier_name, args[i]->clone());
		}

		return env;
	}

	static std::unique_ptr<Object> unwrap_return_value(
		std::unique_ptr<Object> obj)
	{
		if (auto *returnValue = dynamic_cast<ReturnValue *>(obj.get()))
		{
			return std::move(returnValue->value);
		}
		return obj;
	}

	std::unique_ptr<Object> eval(
		ast::Node *node, std::shared_ptr<Environment> env)
	{
		// Statements
		if (auto *program = dynamic_cast<ast::Program *>(node))
		{
			return eval_program(program->statements, env);
		}

		if (auto *expr_stmt = dynamic_cast<ast::ExpressionStatement *>(node))
		{
			return eval(expr_stmt->expression.get(), env);
		}

		if (auto *return_stmt = dynamic_cast<ast::ReturnStatement *>(node))
		{
			auto val = eval(return_stmt->get_return_value().get(), env);
			if (is_error(val.get()))
			{
				return val;
			}
			return std::make_unique<ReturnValue>(std::move(val));
		}

		if (auto *let_stmt = dynamic_cast<ast::LetStatement *>(node))
		{
			auto val = eval(let_stmt->get_value().get(), env);
			if (is_error(val.get()))
			{
				return val;
			}
			env->set(let_stmt->ident->identifier_name, std::move(val));
			return nullptr; // Let statements don't produce a value
		}

		// Expressions
		if (auto *integer_literal = dynamic_cast<ast::IntegerLiteral *>(node))
		{
			return std::make_unique<Integer>(integer_literal->get_value());
		}

		if (auto *identifier = dynamic_cast<ast::Identifier *>(node))
		{
			return eval_identifier(identifier, env);
		}

		if (auto *boolean_literal = dynamic_cast<ast::BooleanLiteral *>(node))
		{
			return native_bool_to_bool_object(boolean_literal->get_value());
		}

		if (auto *prefix_expr = dynamic_cast<ast::PrefixExpression *>(node))
		{
			auto right = eval(prefix_expr->get_right_expression().get(), env);
			if (is_error(right.get()))
			{
				return right;
			}
			return eval_prefix_expression(
				prefix_expr->get_prefix_operator(), right.get());
		}

		if (auto *infix_expr = dynamic_cast<ast::InfixExpression *>(node))
		{
			auto left = eval(infix_expr->get_left().get(), env);
			if (is_error(left.get()))
			{
				return left;
			}
			auto right = eval(infix_expr->get_right().get(), env);
			if (is_error(right.get()))
			{
				return right;
			}
			return eval_infix_expr(infix_expr->get_operator(),
								   left.get(), right.get());
		}

		if (auto *block_stmt = dynamic_cast<ast::BlockStatement *>(node))
		{
			return eval_block_stmt(block_stmt->get_statements(), env);
		}

		if (auto *if_expr = dynamic_cast<ast::IfExpression *>(node))
		{
			return eval_if_expr(if_expr, env);
		}

		if (auto *func_lit = dynamic_cast<ast::FunctionLiteral *>(node))
		{
			std::vector<std::unique_ptr<ast::Identifier>> params;
			for (const auto &p : func_lit->get_parameters())
			{
				auto p_clone = p->clone();
				params.push_back(std::unique_ptr<ast::Identifier>(
					static_cast<ast::Identifier *>(p_clone.release())));
			}

			auto body_clone = func_lit->get_body()->clone();
			auto body_ptr = std::unique_ptr<ast::BlockStatement>(
				static_cast<ast::BlockStatement *>(body_clone.release()));

			return std::make_unique<Function>(
				std::move(params), std::move(body_ptr), env);
		}

		if (auto *call_expr = dynamic_cast<ast::CallExpression *>(node))
		{
			auto function = eval(call_expr->get_function().get(), env);
			if (is_error(function.get()))
			{
				return function;
			}

			auto args = eval_expressions(call_expr->get_arguments(), env);
			if (args.size() == 1 && is_error(args[0].get()))
			{
				return std::move(args[0]);
			}

			return apply_function(function.get(), args);
		}

		return nullptr;
	}
}
