#include "object/error.hpp"

Error::Error(std::string msg) : message(msg) {}

object_type Error::get_type()
{
	return ERROR_OBJ;
}

std::string Error::inspect()
{
	return "ERROR: " + message;
}

std::unique_ptr<Object> Error::clone() const
{
	return std::make_unique<Error>(message);
}
