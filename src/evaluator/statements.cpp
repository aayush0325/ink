#include "internal.hpp"
#include "ast/ast.hpp"

namespace evaluator
{
    std::unique_ptr<Object> eval_block_stmt(
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
                    // Encountered a result/error in a nested block statement...
                    // Returning result here will notify the `eval_program()`
                    // function that the nested block has returned a value
                    // and hence that will be used to signify the return value.
                    return result;
                }
            }
        }

        return result;
    }

    std::unique_ptr<Object> eval_program(
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
                    // If we encounter a return value then stop execution...
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
}
