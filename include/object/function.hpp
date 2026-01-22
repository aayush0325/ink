#pragma once

#include "object/object.hpp"
#include "ast/identifier.hpp"
#include "ast/block_statement.hpp"
#include "object/environment.hpp"
#include <vector>
#include <memory>
#include <sstream>

class Function : public Object
{
public:
	Function(std::vector<std::unique_ptr<ast::Identifier>> params, std::unique_ptr<ast::BlockStatement> body, std::shared_ptr<Environment> env);

	object_type get_type() override;
	std::string inspect() override;
	std::unique_ptr<Object> clone() const override;

	std::vector<std::unique_ptr<ast::Identifier>> parameters;
	std::unique_ptr<ast::BlockStatement> body;
	std::shared_ptr<Environment> env;
};
