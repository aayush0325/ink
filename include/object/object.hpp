#pragma once

#include <string>

typedef std::string object_type;

const object_type INTEGER_OBJ = "INTEGER";
const object_type BOOLEAN_OBJ = "BOOLEAN";
const object_type NULL_OBJ = "NULL";

class Object
{
public:
	virtual object_type get_type() = 0;
	virtual std::string inspect() = 0;
	virtual ~Object() {}
};
