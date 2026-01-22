#include "ast/call_expression.hpp"
#include <sstream>

std::string ast::CallExpression::get_string()
{
	std::stringstream ss;
	ss << function->get_string();
	ss << "(";

	for (size_t i = 0; i < arguments.size(); i++)
	{
		ss << arguments[i]->get_string();
		if (i < arguments.size() - 1)
		{
			ss << ", ";
		}
	}

	ss << ")";
	return ss.str();
}

std::string ast::CallExpression::token_literal()
{
	return token.literal;
}

std::unique_ptr<ast::Node> ast::CallExpression::clone() const
{
	auto clone = std::make_unique<CallExpression>(token);
	if (function)
	{
		auto func_clone = function->clone();
		clone->set_function(std::unique_ptr<Expression>(static_cast<Expression *>(func_clone.release())));
	}
	std::vector<std::unique_ptr<Expression>> args_clone;
	for (const auto &arg : arguments)
	{
		auto arg_clone = arg->clone();
		args_clone.push_back(std::unique_ptr<Expression>(static_cast<Expression *>(arg_clone.release())));
	}
	clone->set_arguments(std::move(args_clone));
	return clone;
}
