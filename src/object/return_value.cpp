#include "object/return_value.hpp"

ReturnValue::ReturnValue(std::unique_ptr<Object> val) : value(std::move(val)) {}

object_type ReturnValue::get_type()
{
	return RETURN_VALUE_OBJ;
}

std::string ReturnValue::inspect()
{
	return value->inspect();
}

std::unique_ptr<Object> ReturnValue::clone() const
{
	return std::make_unique<ReturnValue>(value->clone());
}
