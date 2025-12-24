#pragma once

#include "object/object.hpp"

class Null : public Object
{
public:
	Null() {}

	object_type get_type() override;
	std::string inspect() override;
};
