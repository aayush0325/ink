#pragma once

#include <string>
#include <memory>

typedef std::string object_type;

const object_type INTEGER_OBJ = "INTEGER";
const object_type BOOLEAN_OBJ = "BOOLEAN";
const object_type NULL_OBJ = "NULL";
const object_type ERROR_OBJ = "ERROR";
const object_type RETURN_VALUE_OBJ = "RETURN_VALUE";
const object_type FUNCTION_OBJ = "FUNCTION";
const object_type STRING_OBJ = "STRING";

class Object
{
public:
	virtual object_type get_type() = 0;
	virtual std::string inspect() = 0;
	virtual std::unique_ptr<Object> clone() const = 0;
	virtual ~Object() {}
};
