#pragma once

#include "object/object.hpp"
#include <memory>

class ReturnValue : public Object
{
public:
	std::unique_ptr<Object> value;

	ReturnValue(std::unique_ptr<Object> val);
	virtual object_type get_type() override;
	virtual std::string inspect() override;
	virtual std::unique_ptr<Object> clone() const override;
};
