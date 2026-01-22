#include "object/null.hpp"

object_type Null::get_type()
{
	return NULL_OBJ;
}

std::string Null::inspect()
{
	return "null";
}

std::unique_ptr<Object> Null::clone() const
{
	return std::make_unique<Null>();
}
