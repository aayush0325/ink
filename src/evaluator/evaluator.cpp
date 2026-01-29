#include "internal.hpp"
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
#include "ast/string_literal.hpp"
#include "object/string.hpp"

namespace evaluator
{
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

		if (auto *string_literal = dynamic_cast<ast::StringLiteral *>(node))
		{
			return std::make_unique<String>(string_literal->get_value());
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
								   left.get(),
								   right.get());
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
