#include "internal.hpp"
#include "ast/block_statement.hpp" // For Function body

namespace evaluator
{
    std::unique_ptr<Object> apply_function(
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

    std::shared_ptr<Environment> extend_function_env(
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
}
