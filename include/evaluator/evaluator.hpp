#pragma once

#include "ast/ast.hpp"
#include "object/object.hpp"
#include <memory>

namespace evaluator
{
	std::unique_ptr<Object> eval(ast::Node *node);
}
