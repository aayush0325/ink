#include "internal.hpp"

namespace evaluator
{
    std::unique_ptr<Object> getNull()
    {
        return std::make_unique<Null>();
    }

    std::unique_ptr<Object> native_bool_to_bool_object(bool input)
    {
        return std::make_unique<Boolean>(input);
    }

    bool is_error(Object *obj)
    {
        if (obj != nullptr)
        {
            return obj->get_type() == ERROR_OBJ;
        }
        return false;
    }

    bool is_truthy(Object *obj)
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

    std::unique_ptr<Object> unwrap_return_value(
        std::unique_ptr<Object> obj)
    {
        if (auto *returnValue = dynamic_cast<ReturnValue *>(obj.get()))
        {
            return std::move(returnValue->value);
        }
        return obj;
    }
}
