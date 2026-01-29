#pragma once

#include "evaluator/evaluator.hpp"
#include "object/object.hpp"
#include "object/error.hpp"
#include "object/function.hpp"
#include "object/integer.hpp"
#include "object/boolean.hpp"
#include "object/null.hpp"
#include "object/return_value.hpp"
#include "ast/identifier.hpp"
#include "ast/if_expression.hpp"
#include "ast/ast.hpp"

#include <memory>
#include <vector>
#include <string>
#include <format>

namespace evaluator
{
    // Utils
    std::unique_ptr<Object> getNull();
    std::unique_ptr<Object> native_bool_to_bool_object(bool input);
    bool is_error(Object *obj);
    bool is_truthy(Object *obj);
    std::unique_ptr<Object> unwrap_return_value(std::unique_ptr<Object> obj);

    template <typename... Args>
    std::unique_ptr<Object> new_error(std::string_view format_str, Args &&...args)
    {
        return std::make_unique<Error>(
            std::vformat(format_str, std::make_format_args(args...)));
    }

    // Expressions
    std::unique_ptr<Object> eval_bang_op_expr(Object *right);
    
    std::unique_ptr<Object> eval_prefix_expression(
        const std::string &operator_str,
        Object *right);

    std::unique_ptr<Object> eval_int_infix_expr(
        const std::string &operator_str,
        Object *left,
        Object *right);

    std::unique_ptr<Object> eval_infix_expr(
        const std::string &operator_str,
        Object *left,
        Object *right);

    std::unique_ptr<Object> eval_identifier(
        ast::Identifier *node,
        std::shared_ptr<Environment> env);

    std::unique_ptr<Object> eval_if_expr(
        ast::IfExpression *ie,
        std::shared_ptr<Environment> env);

    std::vector<std::unique_ptr<Object>> eval_expressions(
        const std::vector<std::unique_ptr<ast::Expression>> &exps,
        std::shared_ptr<Environment> env);

    // Statements
    std::unique_ptr<Object> eval_block_stmt(
        const std::vector<std::unique_ptr<ast::Statement>> &statements,
        std::shared_ptr<Environment> env);

    std::unique_ptr<Object> eval_program(
        const std::vector<std::unique_ptr<ast::Statement>> &statements,
        std::shared_ptr<Environment> env);

    // Functions
    std::unique_ptr<Object> apply_function(
        Object *fn,
        const std::vector<std::unique_ptr<Object>> &args);

    std::shared_ptr<Environment> extend_function_env(
        Function *fn,
        const std::vector<std::unique_ptr<Object>> &args);

}
