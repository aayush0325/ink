#pragma once

#include "object/object.hpp"

class Boolean : public Object
{
public:
	bool value;

	Boolean(bool value) : value(value) {}

	object_type get_type() override;
	std::string inspect() override;
};
