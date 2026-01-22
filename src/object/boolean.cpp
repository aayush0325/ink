#include "object/boolean.hpp"

object_type Boolean::get_type()
{
	return BOOLEAN_OBJ;
}

std::string Boolean::inspect()
{
	return value ? "true" : "false";
}

std::unique_ptr<Object> Boolean::clone() const
{
	return std::make_unique<Boolean>(value);
}
