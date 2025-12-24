#include "object/integer.hpp"

object_type Integer::get_type()
{
	return INTEGER_OBJ;
}

std::string Integer::inspect()
{
	return std::to_string(value);
}
