#pragma once

#include "ast/ast.hpp"
#include <vector>
#include <string>

// program node, will be the root of our AST, implements the "Node" abstract class
class Program : public Node
{
public:
	virtual std::string token_literal();

	Program()
	{
		statements.clear();
	}

private:
	// each line will be a statement stored in this vector
	std::vector<Statement> statements;
};