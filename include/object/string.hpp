#pragma once

#include "object/object.hpp"

class String : public Object
{
public:
	String(std::string value) : value(value) {}
	String() : value("") {}

	void set_string(std::string s);
	std::string get_value() { return value; }
	std::string inspect() override;
	object_type get_type() override;
	std::unique_ptr<Object> clone() const override;

private:
	std::string value;
};