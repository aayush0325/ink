#pragma once

#include "object/object.hpp"
#include <cstdint>

class Integer : public Object
{
public:
	int64_t value;

	Integer(int64_t value) : value(value) {}

	object_type get_type() override;
	std::string inspect() override;
};
