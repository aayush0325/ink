#include "object/string.hpp"

void String::set_string(std::string s)
{
	value = s;
}

std::string String::inspect()
{
	return value;
}

object_type String::get_type()
{
	return STRING_OBJ;
}

std::unique_ptr<Object> String::clone() const
{
	return std::make_unique<String>(value);
}
