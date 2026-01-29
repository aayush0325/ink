#include "internal.hpp"
#include "ast/block_statement.hpp" // For BlockStatement in AST if needed, though mostly Expressions here.
// Expressions.cpp mainly deals with expressions.

namespace evaluator
{
    std::unique_ptr<Object> eval_bang_op_expr(Object *right)
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

    std::unique_ptr<Object> eval_prefix_expression(
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

    std::unique_ptr<Object> eval_int_infix_expr(
        const std::string &operator_str,
        Object *left,
        Object *right)
    {
        // Cast to Integer objects
        auto *left_int = dynamic_cast<Integer *>(left);
        auto *right_int = dynamic_cast<Integer *>(right);

        // Verify for type mismatch
        if (!left_int || !right_int)
        {
            return new_error("type mismatch: {} {} {}",
                             left->get_type(), operator_str, right->get_type());
        }

        // Extract values
        int64_t left_val = left_int->value;
        int64_t right_val = right_int->value;

        // Do the specified operation
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

        // Unknown operator
        return new_error("unknown operator: {} {} {}",
                         left->get_type(), operator_str, right->get_type());
    }

    std::unique_ptr<Object> eval_infix_expr(
        const std::string &operator_str,
        Object *left,
        Object *right)
    {
        if (left->get_type() == INTEGER_OBJ && right->get_type() == INTEGER_OBJ)
        {
            return eval_int_infix_expr(operator_str, left, right);
        }

        if (left->get_type() != right->get_type())
        {
            return new_error("type mismatch: {} {} {}",
                             left->get_type(), operator_str, right->get_type());
        }

        return new_error("unknown operator: {} {} {}",
                         left->get_type(), operator_str, right->get_type());
    }

    std::unique_ptr<Object> eval_identifier(
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

    std::unique_ptr<Object> eval_if_expr(
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

    std::vector<std::unique_ptr<Object>> eval_expressions(
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
}
