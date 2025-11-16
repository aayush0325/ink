#pragma once

#include <string>

namespace ast
{
	/*
		Interfaces for all the Nodes in our AST.
		The top level "Program" node has a vector of "Statement" Nodes and a
		"Statement" node may have many types of "Expression" nodes.
	*/

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
}