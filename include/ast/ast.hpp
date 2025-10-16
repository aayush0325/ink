#pragma once

#include <string>

// root abstract base class of a node in our AST
class Node
{
public:
	virtual ~Node() {}
	virtual std::string token_literal() = 0;
	virtual std::string get_string() = 0;
};

// abstract base class for all statement nodes
class Statement : public Node
{
public:
	virtual std::string token_literal() = 0;
	virtual std::string get_string() = 0;
};

// abstract base class for all expression nodes
class Expression : public Node
{
public:
	virtual std::string token_literal() = 0;
	virtual std::string get_string() = 0;
};
