#include "object/null.hpp"

object_type Null::get_type()
{
	return NULL_OBJ;
}

std::string Null::inspect()
{
	return "null";
}
