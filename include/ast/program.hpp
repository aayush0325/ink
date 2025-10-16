#pragma once

#include "ast/ast.hpp"
#include <vector>
#include <string>
#include <memory>

// program node, will be the root of our AST, implements the "Node" abstract class
class Program : public Node
{
public:
	virtual std::string token_literal();
	virtual std::string get_string();

	Program()
	{
		statements.clear();
	}

	// each line will be a statement stored in this vector
	std::vector<std::unique_ptr<Statement>> statements;
};