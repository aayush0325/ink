#pragma once

#include "object/object.hpp"
#include <string>

class Error : public Object
{
public:
	std::string message;

	Error(std::string msg);
	virtual object_type get_type() override;
	virtual std::string inspect() override;
	virtual std::unique_ptr<Object> clone() const override;
};
