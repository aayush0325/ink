#include "object/boolean.hpp"

object_type Boolean::get_type()
{
	return BOOLEAN_OBJ;
}

std::string Boolean::inspect()
{
	return value ? "true" : "false";
}
